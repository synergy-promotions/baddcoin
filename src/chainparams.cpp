// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "BBC NEWS 14/09/2020, coronavirus enters 2nd lockdown in UK";
    const CScript genesisOutputScript = CScript() << ParseHex("04efffc90487376698fa74540d0dcef6ce456bc132a5c7602df5275a65982bf99eeacd5f25894237b4bf9f79697748ae4e94ab2b975bf52ee29f60a1a2df6dd4e4") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.nSubsidyHalvingInterval = 8400000;
        consensus.BIP16Exception = uint256S("0x00");
        consensus.BIP34Height = 0;
        //consensus.BIP34Hash = uint256S("0x2e883b1393a501f22e9c9cefb13ec2ff4cadb1c627372814e81770fa39a92218"); //genesis
	//consensus.BIP34Hash = uint256S("0x00000d693a935464bd31f9fd993474ab0cb467aefea4a5317797ceb958563fb0"); //block 1
	//consensus.BIP34Hash = uint256S("0x00000395a7bcd3f95b1ae06ab3eb3481c3c58cd46b2676fcd2e2db1480db910a"); //block 51
	//consensus.BIP34Hash = uint256S("0x0000000666383ac328619af83777aad0e61e926a428a9049b506ac56ff36accef"); //block 201
        //consensus.BIP34Hash = uint256S("0x00000096016d41ae3e17cc312fb412f92fe2a1ccfc1dbdc113ee32a0a388be33"); //block 2000
        //consensus.BIP34Hash = uint256S("0x0000002ed1e7d63c481dbcecd2ceed5e61a9d2d9b92ac13dca1709e02faf7f84"); //block 5000
	consensus.BIP34Hash = uint256S("0x0000033955ca93157f081fdc9af984377acca48c226bffa8af42e7bd5bc6410d"); //block 80559
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        //consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        //consensus.nPowTargetSpacing = 10 * 60;
        consensus.nPowTargetTimespan = 10 * 30; // Baddcoin: 5 minutes
        consensus.nPowTargetSpacing = 1 * 30; // Baddcoin: 30 seconds 
        //consensus.fPowAllowMinDifficultyBlocks = true; //for premining block 1
        //consensus.fPowNoRetargeting = true; //for premining block 1
        consensus.fPowAllowMinDifficultyBlocks = false; //default false
        consensus.fPowNoRetargeting = false; //default false
        //consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        //consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nRuleChangeActivationThreshold = 30; 
        consensus.nMinerConfirmationWindow = 40; 
        //consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
	//consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
	//consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
	//genesis=consensus.nMinimumChainWork = uint256S("0x00");
	//consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010"); //genesis
	//consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000200011"); //block 1
	//consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000000ee7416f"); //block 51
	//consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000010bcc8647"); //block 201
        //consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000bc0e0e577"); //block 2000
	//consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000018fff76d001"); //block 5000
	consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000002711815d737"); //block 80559

        // By default assume that the signatures in ancestors of this block are valid.
        //consensus.defaultAssumeValid = uint256S("0x2e883b1393a501f22e9c9cefb13ec2ff4cadb1c627372814e81770fa39a92218"); // 0
	//consensus.defaultAssumeValid = uint256S("0x00000d693a935464bd31f9fd993474ab0cb467aefea4a5317797ceb958563fb0"); //block 1
	//consensus.defaultAssumeValid = uint256S("0x00000395a7bcd3f95b1ae06ab3eb3481c3c58cd46b2676fcd2e2db1480db910a"); //block 51
	//consensus.defaultAssumeValid = uint256S("0x000000666383ac328619af83777aad0e61e926a428a9049b506ac56ff36accef"); //block 201
	//consensus.defaultAssumeValid = uint256S("0x00000096016d41ae3e17cc312fb412f92fe2a1ccfc1dbdc113ee32a0a388be33"); //block 2000
	//consensus.defaultAssumeValid = uint256S("0x0000002ed1e7d63c481dbcecd2ceed5e61a9d2d9b92ac13dca1709e02faf7f84"); //block 5000
	consensus.defaultAssumeValid = uint256S("0x0000033955ca93157f081fdc9af984377acca48c226bffa8af42e7bd5bc6410d"); //block 80559


        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        //pchMessageStart[0] = 0xf9;
        //pchMessageStart[1] = 0xbe;
        //pchMessageStart[2] = 0xb4;
        //pchMessageStart[3] = 0xd9;
        //nDefaultPort = 28333;
        //nPruneAfterHeight = 100000;
        //m_assumed_blockchain_size = 320;
        //m_assumed_chain_state_size = 4;
	pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xdc;
        pchMessageStart[2] = 0xeb;
        pchMessageStart[3] = 0xfa;
        nDefaultPort = 28333;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 22;
        m_assumed_chain_state_size = 3;

        //genesis = CreateGenesisBlock(1231006505, 2083236893, 0x1d00ffff, 1, 50 * COIN);
        //consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"));
        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));
	genesis = CreateGenesisBlock(1600081409, 128731164, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x2e883b1393a501f22e9c9cefb13ec2ff4cadb1c627372814e81770fa39a92218"));
        assert(genesis.hashMerkleRoot == uint256S("0x9c539954f1bef19189a04314d8c29632e2870940e13d148f4d9ba421428ef784"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as an addrfetch if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
	//vSeeds.emplace_back("dnsseed.baddcoin.org");

        //base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0);
        //base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        //base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        //base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        //base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        //bech32_hrp = "bc";

	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25); //=B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23); //=A
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0xb2, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0xb2, 0x88, 0xAD, 0xE4};

        bech32_hrp = "badd";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;

        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = {
            {
		{  0, uint256S("0x2e883b1393a501f22e9c9cefb13ec2ff4cadb1c627372814e81770fa39a92218")},
		{  1, uint256S("0x00000d693a935464bd31f9fd993474ab0cb467aefea4a5317797ceb958563fb0")},
                {  51, uint256S("0x00000395a7bcd3f95b1ae06ab3eb3481c3c58cd46b2676fcd2e2db1480db910a")},
		{  201, uint256S("0x000000666383ac328619af83777aad0e61e926a428a9049b506ac56ff36accef")},
                {  2000, uint256S("0x00000096016d41ae3e17cc312fb412f92fe2a1ccfc1dbdc113ee32a0a388be33")},
                {  5000, uint256S("0x0000002ed1e7d63c481dbcecd2ceed5e61a9d2d9b92ac13dca1709e02faf7f84")},
                {  80559, uint256S("0x0000033955ca93157f081fdc9af984377acca48c226bffa8af42e7bd5bc6410d")},
            }
        };

        chainTxData = ChainTxData{
	    //block 2000
            // Data from rpc: getchaintxstats 1999 00000395a7bcd3f95b1ae06ab3eb3481c3c58cd46b2676fcd2e2db1480db910a
            // nTime    1600358171, block1=1600273186,block50=1600280461,block201=1600289744
            // nTxCount 2008, block1=2,block50=52,block201=206
            // dTxRate  0.02362167636183792 block1=1,block50=0.007070135746606335,block201=0.0126354908640446
            //block 5000
            // Data from rpc:  getchaintxstats 4999 "0000002ed1e7d63c481dbcecd2ceed5e61a9d2d9b92ac13dca1709e02faf7f84" 
            // nTime    1622023973, 
            // nTxCount 5034, 
            // dTxRate 0.000231349397312292

            //block 80559
            // Data from rpc:  getchaintxstats 80558 "0000033955ca93157f081fdc9af984377acca48c226bffa8af42e7bd5bc6410d"
            /* nTime    */ 1627218010,
            /* nTxCount */ 80593,
            /* dTxRate  */ 0.002990978039538613
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.nSubsidyHalvingInterval = 8400000;
        consensus.BIP16Exception = uint256S("0x00");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0400d26a9a7c311c61f45699a07586883b05f160eb7e72769e72934b16a2c932");
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 0; //770112; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 0; //834624; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 0; // = 836640; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        //consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        //consensus.nPowTargetSpacing = 10 * 60;
        consensus.nPowTargetTimespan = 10 * 30; // Baddcoin: 5 minutes
        consensus.nPowTargetSpacing = 1 * 30; // Baddcoin: 30 seconds

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 30;
        consensus.nMinerConfirmationWindow = 40; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        //consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000001495c1d5a01e2af8a23");
	consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0400d26a9a7c311c61f45699a07586883b05f160eb7e72769e72934b16a2c932"); // 0

        //pchMessageStart[0] = 0x0b;
        //pchMessageStart[1] = 0x11;
        //pchMessageStart[2] = 0x09;
        //pchMessageStart[3] = 0x07;
        //nDefaultPort = 38333;
        //nPruneAfterHeight = 1000;
        //m_assumed_blockchain_size = 40;
        //m_assumed_chain_state_size = 2;
	pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xe5;
        nDefaultPort = 38333;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 2;
        m_assumed_chain_state_size = 1;

        //genesis = CreateGenesisBlock(1296688602, 414098458, 0x1d00ffff, 1, 50 * COIN);
        //consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"));
        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));
	genesis = CreateGenesisBlock(1600087136, 2085854001, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x0400d26a9a7c311c61f45699a07586883b05f160eb7e72769e72934b16a2c932"));
        assert(genesis.hashMerkleRoot == uint256S("0x9c539954f1bef19189a04314d8c29632e2870940e13d148f4d9ba421428ef784"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.emplace_back("testnet-seed.baddcoin.jonasschnelli.ch");

        //base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        //base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        //base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        //base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        //base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        //bech32_hrp = "tb";
	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); //=b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,65); //=t
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); 
        base58Prefixes[EXT_PUBLIC_KEY] = {0xc3, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0xc3, 0x35, 0x83, 0x94};
        bech32_hrp = "tbadd";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
		{0, uint256S("0x0400d26a9a7c311c61f45699a07586883b05f160eb7e72769e72934b16a2c932")},
            }
        };

        chainTxData = ChainTxData{
            /* nTime    */ 1600087136,
            /* nTxCount */ 0,
            /* dTxRate  */ 0
        };
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 0; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 0; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 0; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        //consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        //consensus.nPowTargetSpacing = 10 * 60;
        consensus.nPowTargetTimespan = 3 * 60 * 60; //(10800)
        consensus.nPowTargetSpacing = 2 * 60; // (120)

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 30; // 75% for testchains
        consensus.nMinerConfirmationWindow = 40; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        //pchMessageStart[0] = 0xfa;
        //pchMessageStart[1] = 0xbf;
        //pchMessageStart[2] = 0xb5;
        //pchMessageStart[3] = 0xda;
        //nDefaultPort = 48444;
        //nPruneAfterHeight = 1000;
        //m_assumed_blockchain_size = 0;
        //m_assumed_chain_state_size = 0;
        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xd1;
        pchMessageStart[3] = 0xfb;
        nDefaultPort = 48444;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        //genesis = CreateGenesisBlock(1296688602, 2, 0x207fffff, 1, 50 * COIN);
        //consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));
	genesis = CreateGenesisBlock(1600087394, 2085764951, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x1ac598aaaa5b8528a6a8d2132be879e84f7161d6b5c2118fdff1f1616f004605"));
        assert(genesis.hashMerkleRoot == uint256S("0x9c539954f1bef19189a04314d8c29632e2870940e13d148f4d9ba421428ef784"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x1ac598aaaa5b8528a6a8d2132be879e84f7161d6b5c2118fdff1f1616f004605")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        //base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        //base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        //base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        //base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        //base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        //bech32_hrp = "bcrt";
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); //=b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,65); //=t
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); //=?
        base58Prefixes[EXT_PUBLIC_KEY] = {0xc3, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0xc3, 0x35, 0x83, 0x94};
        bech32_hrp = "rbadd";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (args.IsArgSet("-segwitheight")) {
        int64_t height = args.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
