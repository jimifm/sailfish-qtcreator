/****************************************************************************
**
** Copyright (C) 2016 Lorenz Haas
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

// Tested with version 2.01, 2.02, 2.02.1, 2.03 and 2.04

#include "artisticstyle.h"

#include "artisticstyleconstants.h"
#include "artisticstyleoptionspage.h"
#include "artisticstylesettings.h"

#include "../beautifierconstants.h"
#include "../beautifierplugin.h"
#include "../command.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/idocument.h>
#include <cppeditor/cppeditorconstants.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/project.h>
#include <utils/fileutils.h>
#include <utils/hostosinfo.h>

#include <QAction>
#include <QMenu>

namespace Beautifier {
namespace Internal {
namespace ArtisticStyle {

ArtisticStyle::ArtisticStyle(BeautifierPlugin *parent) :
    BeautifierAbstractTool(parent),
    m_beautifierPlugin(parent),
    m_settings(new ArtisticStyleSettings)
{
}

ArtisticStyle::~ArtisticStyle()
{
    delete m_settings;
}

bool ArtisticStyle::initialize()
{
    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::ArtisticStyle::MENU_ID);
    menu->menu()->setTitle(QLatin1String(Constants::ArtisticStyle::DISPLAY_NAME));

    m_formatFile = new QAction(BeautifierPlugin::msgFormatCurrentFile(), this);
    menu->addAction(Core::ActionManager::registerAction(m_formatFile,
                                                        Constants::ArtisticStyle::ACTION_FORMATFILE));
    connect(m_formatFile, &QAction::triggered, this, &ArtisticStyle::formatFile);

    Core::ActionManager::actionContainer(Constants::MENU_ID)->addMenu(menu);

    return true;
}

void ArtisticStyle::updateActions(Core::IEditor *editor)
{
    m_formatFile->setEnabled(editor && editor->document()->id() == CppEditor::Constants::CPPEDITOR_ID);
}

QList<QObject *> ArtisticStyle::autoReleaseObjects()
{
    ArtisticStyleOptionsPage *optionsPage = new ArtisticStyleOptionsPage(m_settings, this);
    return QList<QObject *>() << optionsPage;
}

void ArtisticStyle::formatFile()
{
    const QString cfgFileName = configurationFile();
    if (cfgFileName.isEmpty()) {
        BeautifierPlugin::showError(BeautifierPlugin::msgCannotGetConfigurationFile(
                                        QLatin1String(Constants::ArtisticStyle::DISPLAY_NAME)));
    } else {
        m_beautifierPlugin->formatCurrentFile(command(cfgFileName));
    }
}

QString ArtisticStyle::configurationFile() const
{
    if (m_settings->useCustomStyle())
        return m_settings->styleFileName(m_settings->customStyle());

    if (m_settings->useOtherFiles()) {
        if (const ProjectExplorer::Project *project
                = ProjectExplorer::ProjectTree::currentProject()) {
            const QStringList files = project->files(ProjectExplorer::Project::AllFiles);
            foreach (const QString &file, files) {
                if (!file.endsWith(QLatin1String(".astylerc")))
                    continue;
                const QFileInfo fi(file);
                if (fi.isReadable())
                    return file;
            }
        }
    }

    if (m_settings->useHomeFile()) {
        const QDir homeDirectory = QDir::home();
        QString file = homeDirectory.filePath(QLatin1String(".astylerc"));
        if (QFile::exists(file))
            return file;
        file = homeDirectory.filePath(QLatin1String("astylerc"));
        if (QFile::exists(file))
            return file;
    }

    return QString();
}

Command ArtisticStyle::command(const QString &cfgFile) const
{
    Command command;
    command.setExecutable(m_settings->command());
    command.addOption(QLatin1String("-q"));
    command.addOption(QLatin1String("--options=") + cfgFile);

    if (m_settings->version() > ArtisticStyleSettings::Version_2_03) {
        command.setProcessing(Command::PipeProcessing);
        command.setPipeAddsNewline(true);
        command.setReturnsCRLF(Utils::HostOsInfo::isWindowsHost());
    } else {
        command.addOption(QLatin1String("%file"));
    }

    return command;
}

} // namespace ArtisticStyle
} // namespace Internal
} // namespace Beautifier
