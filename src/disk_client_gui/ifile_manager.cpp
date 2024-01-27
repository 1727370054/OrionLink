#include "ifile_manager.h"

iFileManager* iFileManager::instance_ = nullptr;

iFileManager::iFileManager(QObject *parent)
    : QObject(parent)
{}

iFileManager::~iFileManager()
{}
