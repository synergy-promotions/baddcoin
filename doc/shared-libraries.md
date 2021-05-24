Shared Libraries
================

## baddcoinconsensus

The purpose of this library is to make the verification functionality that is critical to Baddcoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `baddcoinconsensus.h` located in `src/script/baddcoinconsensus.h`.

#### Version

`baddcoinconsensus_version` returns an `unsigned int` with the API version *(currently `1`)*.

#### Script Validation

`baddcoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `baddcoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/baddcoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/baddcoin/bips/blob/master/bip-0066.mediawiki)) compliance
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/baddcoin/bips/blob/master/bip-0147.mediawiki))
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/baddcoin/bips/blob/master/bip-0065.mediawiki))
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/baddcoin/bips/blob/master/bip-0112.mediawiki))
- `baddcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/baddcoin/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `baddcoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `baddcoinconsensus_verify_script` for the verification status)*
- `baddcoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `baddcoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `baddcoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `baddcoinconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NBaddcoin](https://github.com/NicolasDorier/NBaddcoin/blob/master/NBaddcoin/Script.cs#L814) (.NET Bindings)
- [node-libbaddcoinconsensus](https://github.com/bitpay/node-libbaddcoinconsensus) (Node.js Bindings)
- [java-libbaddcoinconsensus](https://github.com/dexX7/java-libbaddcoinconsensus) (Java Bindings)
- [baddcoinconsensus-php](https://github.com/Bit-Wasp/baddcoinconsensus-php) (PHP Bindings)
