/****************************************************************************
**
** Copyright (C) 2012 - 2014 Jolla Ltd.
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

#include "merhardwaredevicewizard.h"

#include <ssh/sshconnection.h>

using namespace ProjectExplorer;
using namespace QSsh;

namespace Mer {
namespace Internal {

MerHardwareDeviceWizard::MerHardwareDeviceWizard(QWidget *parent)
    : QWizard(parent),
      m_selectionPage(this),
      m_setupPage(this),
      m_finalPage(this)
{
    setWindowTitle(tr("New Sailfish OS Hardware Device Setup"));
    addPage(&m_selectionPage);
    addPage(&m_setupPage);
    addPage(&m_finalPage);
    m_finalPage.setCommitPage(true);
}

MerHardwareDeviceWizard::~MerHardwareDeviceWizard()
{

}

QString MerHardwareDeviceWizard::hostName() const
{
    return m_selectionPage.hostName();
}

QString MerHardwareDeviceWizard::userName() const
{
    return m_selectionPage.userName();
}

QString MerHardwareDeviceWizard::password() const
{
    return m_selectionPage.password();
}

Abi::Architecture MerHardwareDeviceWizard::architecture() const
{
    return m_selectionPage.architecture();
}

QString MerHardwareDeviceWizard::deviceName() const
{
    return m_selectionPage.deviceName();
}

QString MerHardwareDeviceWizard::privateKeyFilePath() const
{
    return m_setupPage.privateKeyFilePath();
}

QString MerHardwareDeviceWizard::publicKeyFilePath() const
{
    return m_setupPage.publicKeyFilePath();
}

QString MerHardwareDeviceWizard::configurationName() const
{
    return m_setupPage.configName();
}

QString MerHardwareDeviceWizard::freePorts() const
{
     return m_setupPage.freePorts();
}

int MerHardwareDeviceWizard::sshPort() const
{
    return m_selectionPage.sshPort();
}

int MerHardwareDeviceWizard::timeout() const
{
    return m_selectionPage.timeout();
}

bool MerHardwareDeviceWizard::isNewSshKeysRquired() const
{
    return m_setupPage.isNewSshKeysRquired();
}

QString MerHardwareDeviceWizard::sharedSshPath() const
{
    return m_setupPage.sharedSshPath();
}

} // Internal
} // Mer
