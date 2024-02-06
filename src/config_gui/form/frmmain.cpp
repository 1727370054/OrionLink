#include "log_client.h"
#include "config_client.h"
#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "quihelper.h"
#include "login_gui.h"
#include "tools.h"

#include <string>
#include <fstream>
#include <QString>
#include <QTimer>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

static frmMain* cur_frmMain = nullptr;
static void SMessgeCB(MsgCBType type,bool is_ok, const char* desc);

frmMain::frmMain(QWidget *parent) : QDialog(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
    cur_frmMain = this;
    this->initForm();
    Refresh();
    ConfigClient::GetInstance()->set_config_res_cb(SMessgeCB);
    connect(this, &frmMain::SigSaveMessgeCB, this, &frmMain::SaveMessgeCB);
    connect(this, &frmMain::SigDelMessgeCB, this, &frmMain::DelMessgeCB);
    config_row_count_ = ui->formLayout->rowCount();
    if (!config_) config_ = new msg::Config();
}

frmMain::~frmMain()
{
    delete ui;
    cur_frmMain = nullptr;
    delete config_;
    config_ = nullptr;
}

void frmMain::Refresh()
{
    /// 情况历史列表
    AddLog("清理配置列表");
    while (ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
    /// 从配置中心获取配置列表
    /// 断开重连，如果修改了配置
    std::string server_ip = ui->server_ip_edit->text().toStdString();
    int server_port = ui->server_port_box->value();
    std::stringstream ss;
    ss << "server_ip: " << server_ip << " server_port: " << server_port;
    LOGDEBUG(ss.str().c_str());

    /// 关闭之前的连接，重新建立连接
    ConfigClient::GetInstance()->set_auto_delete(false);
    ConfigClient::GetInstance()->Close();
    ConfigClient::GetInstance()->set_server_ip(server_ip.c_str());
    ConfigClient::GetInstance()->set_server_port(server_port);

    if (!ConfigClient::GetInstance()->AutoConnect(2))
    {
        AddLog("连接配置中心失败");
        return;
    }
    AddLog("连接配置中心成功");

    /// 从配置中心获取列表
    auto confs = ConfigClient::GetInstance()->GetAllConfig(1, 100, 2);
    LOGDEBUG(confs.DebugString());

    /// 插入获取的列表
    int row_size = confs.configs_size();
    ui->tableWidget->setRowCount(row_size);
    for (int i = 0; i < row_size; i++)
    {
        auto conf = confs.configs(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(conf.service_name().c_str()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(conf.service_ip().c_str()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(std::to_string(conf.service_port()).c_str()));
    }
    AddLog("更新配置列表完成");
}

void frmMain::AddLog(const char* log)
{
    QString str;
    auto t = QTime::currentTime().toString("HH:mm:ss");
    str = t;
    str += " ";
    str += log;
    ui->log_list_Widget->insertItem(0, new QListWidgetItem(str));
}

void frmMain::DelConfig()
{
    if (ui->tableWidget->rowCount() == 0) return;
    int row = ui->tableWidget->currentRow();
    if (row < 0) return;
    auto item_name = ui->tableWidget->item(row, 0);
    auto item_ip = ui->tableWidget->item(row, 1);
    auto item_port = ui->tableWidget->item(row, 2);
    std::string service_name = item_name->text().toStdString();
    std::string service_ip = item_ip->text().toStdString();
    int service_port = std::atoi(item_port->text().toStdString().c_str());
    std::stringstream ss;
    ss << "您确定要删除 " << service_name << " " << 
        service_ip << ":" << service_port << " 微服务配置信息";
    if (QMessageBox::information(this, "select", ss.str().c_str(),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
    {
        return;
    }
    ConfigClient::GetInstance()->DeleteConfigReq(service_ip.c_str(), service_port);
    std::stringstream info;
    info << "删除 " << service_name << " " <<
        service_ip << ":" << service_port << " 微服务配置信息";
    AddLog(info.str().c_str());
}

void frmMain::InitGUI()
{
    /// 清理上一次的配置项
    while (ui->formLayout->rowCount() != config_row_count_)
    {
        ui->formLayout->removeRow(config_row_count_);
    }

    /// 微服务配置基础信息
    if (config_)
    {
        ui->service_nameLineEdit->setText(config_->service_name().c_str());
        ui->service_ipLineEdit->setText(config_->service_ip().c_str());
        ui->service_portBox->setValue(config_->service_port());
        ui->proto_textEdit->setText(config_->protocol().c_str());
    }
    if (!dynamic_msg_) return;
    ui->type_lineEdit->setText(dynamic_msg_->GetTypeName().c_str());

    /// 通过反射生成界面，设置值
    auto desc = dynamic_msg_->GetDescriptor();
    auto ref = dynamic_msg_->GetReflection();
    /// 遍历字段
    int field_count = desc->field_count();
    std::string style_sheet = "font: 12pt 'Arial'; color: rgb(225, 225, 225);";
    for (int i = 0; i < field_count; i++)
    {
        /// 目前只支持整形、浮点、字符串、枚举、bool
        /// 单个字段描述
        auto field = desc->field(i);
        auto type = field->type();
        /// 存储整形
        QSpinBox* int_box = nullptr;
        /// 浮点型
        QDoubleSpinBox* double_box = nullptr;
        /// 字符串
        QLineEdit* string_edit = nullptr;
        /// bool 枚举
        QComboBox* combo_box = nullptr;

        QLabel* label = new QLabel();
        label->setStyleSheet(style_sheet.c_str());
        label->setText(field->name().c_str());
        switch (type)
        {
        case google::protobuf::FieldDescriptor::TYPE_INT64:
        {
            int_box = new QSpinBox();
            int_box->setMaximum(INT64_MAX);
            int_box->setValue(ref->GetInt64(*dynamic_msg_, field));
            ui->formLayout->addRow(label, int_box);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_INT32:
        {
            int_box = new QSpinBox();
            int_box->setMaximum(INT32_MAX);
            int_box->setValue(ref->GetInt32(*dynamic_msg_, field));
            ui->formLayout->addRow(label, int_box);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
        {
            double_box = new QDoubleSpinBox();
            double_box->setMaximum(DBL_MAX);
            double_box->setValue(ref->GetDouble(*dynamic_msg_, field));
            ui->formLayout->addRow(label, double_box);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_FLOAT:
        {
            double_box = new QDoubleSpinBox();
            double_box->setMaximum(FLT_MAX);
            double_box->setValue(ref->GetFloat(*dynamic_msg_, field));
            ui->formLayout->addRow(label, double_box);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_BYTES:
        case google::protobuf::FieldDescriptor::TYPE_STRING:
        {
            string_edit = new QLineEdit();
            string_edit->setText(ref->GetString(*dynamic_msg_, field).c_str());
            ui->formLayout->addRow(label, string_edit);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_BOOL:
        {
            combo_box = new QComboBox();
            combo_box->addItem("是", true);
            combo_box->addItem("否", false);
            if (ref->GetBool(*dynamic_msg_, field))
                combo_box->setCurrentIndex(0);
            else
                combo_box->setCurrentIndex(1);
            ui->formLayout->addRow(label, combo_box);
        }
        break;
        case google::protobuf::FieldDescriptor::TYPE_ENUM:
        {
            combo_box = new QComboBox();
            for (int j = 0; j < field->enum_type()->value_count(); j++)
            {
                std::string enum_name = field->enum_type()->value(j)->name();
                int enum_value = field->enum_type()->value(j)->number();
                combo_box->addItem(enum_name.c_str(), enum_value);
            }
            ui->formLayout->addRow(label, combo_box);
            /// 获取值对应的索引
            combo_box->setCurrentIndex(combo_box->findData(ref->GetEnumValue(*dynamic_msg_, field)));
        }
        break;
        default:
            break;
        }
    }
}

bool frmMain::LoadConfig(const char* service_ip, int service_port)
{
    ui->stackedWidget->setCurrentIndex(1);
    /// 发送消息获取配置项(Config)
    ConfigClient::GetInstance()->LoadConfigReq(service_ip, service_port);

    if (!config_)
        config_ = new msg::Config();
    bool is_get = false;
    /// 1秒后超时返回
    for (int i = 0; i < 100; i++)
    {
        if (ConfigClient::GetInstance()->GetConfig(service_ip, service_port, config_))
        {
            is_get = true;
            break;
        }
        this_thread::sleep_for(10ms);
    }
    if (!is_get)
    {
        LOGDEBUG("get config data failed!");
        return false;
    }
    LOGDEBUG("get config data success!");
    if (config_->protocol().empty())
    {
        LOGDEBUG("config_ protocol field is empty!");
        return false;
    }
    /// 写入proto文件
    string proto_file_path = "tmp.proto";
    ofstream ofs(proto_file_path);
    ofs << config_->protocol();
    ofs.close();
    /// 加载proto，生成message
    string proto_code = "";
    dynamic_msg_ = ConfigClient::GetInstance()->LoadProto(proto_file_path, "", proto_code);
    if (!dynamic_msg_)
    {
        LOGDEBUG("download proto file failed!");
        return false;
    }
    /// message反序列化
    if (!dynamic_msg_->ParseFromString(config_->private_pb()))
    {
        LOGDEBUG("ParseFromString failed!");
        return false;
    }
    LOGDEBUG(dynamic_msg_->DebugString().c_str());
    /// 根据message生成界面
    /// 根据message内容生成到界面
    InitGUI();

    return true;
}

void frmMain::EditConfig()
{
    if (ui->tableWidget->rowCount() == 0) return;
    int row = ui->tableWidget->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "提示", "请选择需要编辑的配置");
        return;
    }
    /// 获取需要编辑的配置
    auto item_ip = ui->tableWidget->item(row, 1);
    auto item_port = ui->tableWidget->item(row, 2);
    std::string service_ip = item_ip->text().toStdString();
    int service_port = std::atoi(item_port->text().toStdString().c_str());
    /// 打开配置页面并获取配置
    if (!LoadConfig(service_ip.c_str(), service_port))
    {
        AddLog("修改配置失败!");
        return;
    }
    AddLog("修改配置成功!");
}

void frmMain::SaveMessgeCB(bool is_ok, const char* desc)
{
    if (!is_ok)
    {
        std::string error = "上传配置失败! ";
        error += desc;
        QMessageBox::information(this, "info", error.c_str());
    }
    QMessageBox::information(this, "info", "上传配置成功!");
    Refresh();
}

void frmMain::DelMessgeCB(bool is_ok, const char* desc)
{
    if (!is_ok)
    {
        std::string error = "删除配置失败! ";
        error += desc;
        AddLog(error.c_str());
    }
    AddLog("删除配置成功!");
    Refresh();
}

static void SMessgeCB(MsgCBType type, bool is_ok, const char* desc)
{
    if (cur_frmMain)
    {
        switch (type)
        {
        case MSG_SAVE_TYPE:
            cur_frmMain->SigSaveMessgeCB(is_ok, desc);
            break;
        case MSG_DEL_TYPE:
            cur_frmMain->SigDelMessgeCB(is_ok, desc);
            break;
        default:
            break;
        }
    }
}

void frmMain::Save()
{
    if (!dynamic_msg_)
    {
        LOGDEBUG("frmMain::Save failed! dynamic_msg_ is null");
        QMessageBox::information(this, "error", "未加载proto文件或proto文件是空");
        return;
    }
    if (ui->service_nameLineEdit->text().isEmpty()
        || ui->service_ipLineEdit->text().isEmpty()
        || ui->proto_textEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this, "error", "服务名称、IP、proto其中一项为空");
        return;
    }

    /// 将界面输入存储到message中
    /// 遍历界面, 要区分基础信息和配置信息
    
    /// 获取类型描述
    auto desc = dynamic_msg_->GetDescriptor();
    /// 获取反射对象
    auto ref = dynamic_msg_->GetReflection();
    for (int i = config_row_count_; i < ui->formLayout->rowCount(); i++)
    {
        /// 找到key，label的text
        auto label_item = ui->formLayout->itemAt(i, QFormLayout::LabelRole);
        if (!label_item) continue;
        QLabel* label = dynamic_cast<QLabel*>(label_item->widget());
        if (!label) continue;
        std::string field_name = label->text().toStdString();
        /// 找到value，输入控件中的值 整形、枚举、浮点、字符串、bool
        auto field_item = ui->formLayout->itemAt(i, QFormLayout::FieldRole);
        if (!field_item) continue;
        auto field_edit = field_item->widget();
        auto field_desc = desc->FindFieldByName(field_name);
        auto type = field_desc->type();

        /// 存储整形
        QSpinBox* int_box = nullptr;
        /// 浮点型
        QDoubleSpinBox* double_box = nullptr;
        /// 字符串
        QLineEdit* string_edit = nullptr;
        /// bool 枚举
        QComboBox* combo_box = nullptr;
        /// 获取控件的值，设置到message
        switch (type)
        {
        case google::protobuf::FieldDescriptor::TYPE_INT64:
            int_box = dynamic_cast<QSpinBox*>(field_edit);
            if (!int_box) continue;
            ref->SetInt64(dynamic_msg_, field_desc, int_box->value());
            break;
        case google::protobuf::FieldDescriptor::TYPE_INT32:
            int_box = dynamic_cast<QSpinBox*>(field_edit);
            if (!int_box) continue;
            ref->SetInt32(dynamic_msg_, field_desc, int_box->value());
            break;
        case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
            double_box = dynamic_cast<QDoubleSpinBox*>(field_edit);
            if (!double_box) continue;
            ref->SetDouble(dynamic_msg_, field_desc, double_box->value());
            break;
        case google::protobuf::FieldDescriptor::TYPE_FLOAT:
            double_box = dynamic_cast<QDoubleSpinBox*>(field_edit);
            if (!double_box) continue;
            ref->SetFloat(dynamic_msg_, field_desc, double_box->value());
            break;
        case google::protobuf::FieldDescriptor::TYPE_BYTES:
        case google::protobuf::FieldDescriptor::TYPE_STRING:
            string_edit = dynamic_cast<QLineEdit*>(field_edit);
            if (!string_edit) continue;
            ref->SetString(dynamic_msg_, field_desc, string_edit->text().toStdString());
            break;
        case google::protobuf::FieldDescriptor::TYPE_BOOL:
            combo_box = dynamic_cast<QComboBox*>(field_edit);
            if (!combo_box) continue;
            ref->SetBool(dynamic_msg_, field_desc, combo_box->currentData().toBool());
            break;
        case google::protobuf::FieldDescriptor::TYPE_ENUM:
            combo_box = dynamic_cast<QComboBox*>(field_edit);
            if (!combo_box) continue;
            ref->SetEnumValue(dynamic_msg_, field_desc, combo_box->currentData().toInt());
            break;
        default:
            break;
        }
    }
    msg::Config config;
    /// 基础信息
    config.set_service_name(ui->service_nameLineEdit->text().toStdString());
    config.set_service_ip(ui->service_ipLineEdit->text().toStdString());
    config.set_service_port(ui->service_portBox->value());
    config.set_protocol(ui->proto_textEdit->toPlainText().toStdString());
    /// 配置信息
    /// 序列化message
    std::string pb = dynamic_msg_->SerializeAsString();
    config.set_private_pb(pb);
    /// 发送配置信息到配置中心
    ConfigClient::GetInstance()->SendConfigReq(&config);
}

void frmMain::LoadProto()
{
    LOGDEBUG("LoadProto begin");
    while (ui->formLayout->rowCount() != config_row_count_)
    {
        ui->formLayout->removeRow(config_row_count_);
    }

    AddLog("开始加载proto文件");
    /// 用户选择proto文件
    /// 用户输入类型名称，如果没有名称，则使用proto文件中的第一个类型
    QString class_name = ui->type_lineEdit->text();
    std::string class_name_str = "";
    if (!class_name.isEmpty())
    {
        class_name_str = class_name.toStdString();
    }
    QString filename = QFileDialog::getOpenFileName(this, 
        "请选择proto文件", "", "*.proto");
    if (filename.isEmpty())
        return;
    LOGDEBUG(filename.toStdString().c_str());

    std::string proto_code = "";
    dynamic_msg_ = ConfigClient::GetInstance()->LoadProto(filename.toStdString(),
        class_name_str, proto_code);
    if (dynamic_msg_ == NULL)
    {
        AddLog("加载proto文件失败!");
        return;
    }
    AddLog("加载proto文件成功!");
    config_->set_protocol(proto_code);
    InitGUI();
}

void frmMain::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void frmMain::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(QUIHelper::getScreenRect());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void frmMain::on_btnMenu_Close_clicked()
{
    close();
}

bool frmMain::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (watched == ui->widgetTitle) {
            on_btnMenu_Max_clicked();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

std::string frmMain::UTF8ToGBK(const char* data)
{
    std::string ret;
    QString utf8String = QString::fromUtf8(data);
    // 创建一个QTextCodec对象，用于进行编码转换
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");

    // 使用QTextCodec将UTF-8字符串转换为GBK编码
    QByteArray gbkData = codec->fromUnicode(utf8String);
    ret = gbkData.toStdString();
    return ret;
}

void frmMain::initForm()
{
    //设置无边框
    QUIHelper::setFramelessForm(this);
    //设置图标
    IconHelper::setIcon(ui->labIco, 0xf099, 35);
    IconHelper::setIcon(ui->btnMenu_Min, 0xf068);
    IconHelper::setIcon(ui->btnMenu_Max, 0xf067);
    IconHelper::setIcon(ui->btnMenu_Close, 0xf00d);

    //ui->widgetMenu->setVisible(false);
    ui->widgetTitle->installEventFilter(this);
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");

    QFont font;
    font.setPixelSize(25);
    ui->labTitle->setFont(font);
    ui->labTitle->setText("OrionLink微服务管理中心");
    this->setWindowTitle(ui->labTitle->text());

    ui->stackedWidget->setStyleSheet("QLabel{font:60px;}");

    //单独设置指示器大小
    int addWidth = 20;
    int addHeight = 10;
    int rbtnWidth = 15;
    int ckWidth = 13;
    int scrWidth = 12;
    int borderWidth = 3;

    QStringList qss;
    qss << QString("QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{width:%1px;}").arg(addWidth);
    qss << QString("QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,"
        "QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{width:%1px;height:%1px;right:2px;}").arg(addHeight);
    qss << QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth);
    qss << QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth);
    qss << QString("QScrollBar:horizontal{min-height:%1px;border-radius:%2px;}QScrollBar::handle:horizontal{border-radius:%2px;}"
        "QScrollBar:vertical{min-width:%1px;border-radius:%2px;}QScrollBar::handle:vertical{border-radius:%2px;}").arg(scrWidth).arg(scrWidth / 2);
    qss << QString("QWidget#widget_top>QToolButton:pressed,QWidget#widget_top>QToolButton:hover,"
        "QWidget#widget_top>QToolButton:checked,QWidget#widget_top>QLabel:hover{"
        "border-width:0px 0px %1px 0px;}").arg(borderWidth);
    qss << QString("QWidget#widgetleft>QPushButton:checked,QWidget#widgetleft>QToolButton:checked,"
        "QWidget#widgetleft>QPushButton:pressed,QWidget#widgetleft>QToolButton:pressed{"
        "border-width:0px 0px 0px %1px;}").arg(borderWidth);
    this->setStyleSheet(qss.join(""));

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton*> tbtns = ui->widgetTop->findChildren<QToolButton*>();
    foreach(QToolButton * btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();
}

void frmMain::buttonClick()
{
    QToolButton* b = (QToolButton*)sender();
    QString name = b->text();

    QList<QToolButton*> tbtns = ui->widgetTop->findChildren<QToolButton*>();
    foreach(QToolButton * btn, tbtns) {
        btn->setChecked(btn == b);
    }

    if (name == "主界面") {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (name == "添加配置") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "查询配置") {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (name == "调试帮助") {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if (name == "用户退出") {
        exit(0);
    }
}
