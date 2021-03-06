/****************************************************************************
**
** Copyright (C) 2016 BogDan Vatra <bog_dan_ro@yahoo.com>
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

#ifndef ANDROIDCREATEKEYSTORECERTIFICATE_H
#define ANDROIDCREATEKEYSTORECERTIFICATE_H

#include <utils/fileutils.h>

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AndroidCreateKeystoreCertificate; }
QT_END_NAMESPACE

namespace Android {
namespace Internal {

class AndroidCreateKeystoreCertificate : public QDialog
{
    Q_OBJECT
    enum PasswordStatus
    {
        Invalid,
        NoMatch,
        Match
    };

public:
    explicit AndroidCreateKeystoreCertificate(QWidget *parent = 0);
    ~AndroidCreateKeystoreCertificate();
    Utils::FileName keystoreFilePath();
    QString keystorePassword();
    QString certificateAlias();
    QString certificatePassword();

private slots:
    PasswordStatus checkKeystorePassword();
    PasswordStatus checkCertificatePassword();
    bool checkCertificateAlias();
    bool checkCountryCode();
    void on_keystoreShowPassCheckBox_stateChanged(int state);
    void on_certificateShowPassCheckBox_stateChanged(int state);
    void on_buttonBox_accepted();
    void on_samePasswordCheckBox_stateChanged(int state);

private:
    bool validateUserInput();
    Ui::AndroidCreateKeystoreCertificate *ui;
    Utils::FileName m_keystoreFilePath;
};

} // namespace Internal
} // namespace Android

#endif // ANDROIDCREATEKEYSTORECERTIFICATE_H
