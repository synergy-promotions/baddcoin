// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BADDCOIN_QT_BADDCOINADDRESSVALIDATOR_H
#define BADDCOIN_QT_BADDCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BaddcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BaddcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Baddcoin address widget validator, checks for a valid baddcoin address.
 */
class BaddcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BaddcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // BADDCOIN_QT_BADDCOINADDRESSVALIDATOR_H
