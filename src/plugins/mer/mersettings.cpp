/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd.
** Contact: http://jolla.com/
**
** This file is part of Qt Creator.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Digia.
**
****************************************************************************/

#include "mersettings.h"

#include <QFileInfo>

#include <coreplugin/icore.h>

using Core::ICore;

namespace Mer {
namespace Internal {

namespace {
const char SETTINGS_CATEGORY[] = "Mer";
const char RPM_VALIDATION_BY_DEFAULT_KEY[] = "RpmValidationByDefault";
const char QML_LIVE_BENCH_LOCATION_KEY[] = "QmlLiveBenchLocation";
}

MerSettings *MerSettings::s_instance = 0;

MerSettings::MerSettings(QObject *parent)
    : QObject(parent)
    , m_rpmValidationByDefault(true)
    , m_syncQmlLiveWorkspaceEnabled(true)
{
    Q_ASSERT(s_instance == 0);
    s_instance = this;

    read();
}

MerSettings::~MerSettings()
{
    save();

    s_instance = 0;
}

MerSettings *MerSettings::instance()
{
    Q_ASSERT(s_instance != 0);

    return s_instance;
}

bool MerSettings::rpmValidationByDefault()
{
    Q_ASSERT(s_instance);

    return s_instance->m_rpmValidationByDefault;
}

void MerSettings::setRpmValidationByDefault(bool byDefault)
{
    Q_ASSERT(s_instance);

    if (s_instance->m_rpmValidationByDefault == byDefault)
        return;

    s_instance->m_rpmValidationByDefault = byDefault;

    emit s_instance->rpmValidationByDefaultChanged(s_instance->m_rpmValidationByDefault);
}

QString MerSettings::qmlLiveBenchLocation()
{
    Q_ASSERT(s_instance);

    return s_instance->m_qmlLiveBenchLocation;
}

void MerSettings::setQmlLiveBenchLocation(const QString &location)
{
    Q_ASSERT(s_instance);

    if (s_instance->m_qmlLiveBenchLocation == location)
        return;

    s_instance->m_qmlLiveBenchLocation = location;

    emit s_instance->qmlLiveBenchLocationChanged(s_instance->m_qmlLiveBenchLocation);
}

bool MerSettings::hasValidQmlLiveBenchLocation()
{
    Q_ASSERT(s_instance);

    return QFileInfo(s_instance->m_qmlLiveBenchLocation).isExecutable();
}

bool MerSettings::isSyncQmlLiveWorkspaceEnabled()
{
    Q_ASSERT(s_instance);

    return s_instance->m_syncQmlLiveWorkspaceEnabled;
}

void MerSettings::setSyncQmlLiveWorkspaceEnabled(bool enable)
{
    Q_ASSERT(s_instance);

    if (s_instance->m_syncQmlLiveWorkspaceEnabled == enable)
        return;

    s_instance->m_syncQmlLiveWorkspaceEnabled = enable;

    emit s_instance->syncQmlLiveWorkspaceEnabledChanged(s_instance->m_syncQmlLiveWorkspaceEnabled);
}

void MerSettings::read()
{
    QSettings *settings = ICore::settings();
    settings->beginGroup(QLatin1String(SETTINGS_CATEGORY));

    m_rpmValidationByDefault = settings->value(QLatin1String(RPM_VALIDATION_BY_DEFAULT_KEY),
            true).toBool();
    m_qmlLiveBenchLocation = settings->value(QLatin1String(QML_LIVE_BENCH_LOCATION_KEY)).toString();

    settings->endGroup();
}

void MerSettings::save()
{
    QSettings *settings = ICore::settings();
    settings->beginGroup(QLatin1String(SETTINGS_CATEGORY));

    settings->setValue(QLatin1String(RPM_VALIDATION_BY_DEFAULT_KEY), m_rpmValidationByDefault);
    settings->setValue(QLatin1String(QML_LIVE_BENCH_LOCATION_KEY), m_qmlLiveBenchLocation);

    settings->endGroup();
}

} // Internal
} // Mer
