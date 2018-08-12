// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0xc6c74b0a, 0x6baafdeb, 0xa2f3d1bc, 0xbce287b5, 0xbce287b8, 0x688361e5, 0xb23e116a, 0x80c789bb,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 45591;
        nRPCPort = 45592;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;

        // PoSV
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        nLastProofOfWorkHeight = 490000 - 1;
        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        const char* pszTimestamp = "July 26st 2018 was just perfect day...";
        CTransaction txNew(1532552400);
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1532552400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 3207966;

        hashGenesisBlock = genesis.GetHash();






    if(false)
    {
        printf("Searching for genesis block...\n");
        // This will figure out a valid hash and Nonce if you're
        // creating a different genesis block:
        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        uint256 thash;
        char scratchpad[SCRYPT_SCRATCHPAD_SIZE];

        while(true)
        {
            scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
            if (thash <= hashTarget)
                break;
            if ((genesis.nNonce & 0xFFF) == 0)
            {
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
            }
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time\n");
                ++genesis.nTime;
            }
        }
        printf("block.nTime = %u \n", genesis.nTime);
        printf("block.nNonce = %u \n", genesis.nNonce);
        printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());

        printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

    }


        assert(hashGenesisBlock == uint256("0xbe3ccf25f79bc3c8832bde8c0081cc28c88736f91ae9648879af9ae31a470ef8"));
        assert(genesis.hashMerkleRoot == uint256("0xbc921214f9688340097ea0bf9fdf912e4fe5b7f3d3cb5cf2c863fc9280704138"));

        vSeeds.push_back(CDNSSeedData("zija.icu", "seed0.zija.icu"));
        vSeeds.push_back(CDNSSeedData("node1.zija.icu", "node1.zija.icu"));
        vSeeds.push_back(CDNSSeedData("node2.zija.icu", "node2.zija.icu"));
        vSeeds.push_back(CDNSSeedData("node3.zija.icu", "node3.zija.icu"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,189);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("048b75ab041ee9965f6f57ee299395c02daf5105f208fc49e908804aad3ace5a77c7f87b3aae74d6698124f20c3d1bea31c9fcdd350c9c61c0113fd988ecfb5c09");
        nDefaultPort = 46591;
        nRPCPort = 46592;
        strDataDir = "testnet3";
        nLastProofOfWorkHeight = 350 - 1; // Last POW block

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        // CTransaction txGenesis = genesis.vtx[0];
        genesis.nTime = 1532552400;
        // genesis.vtx[0] = txGenesis;
        genesis.nNonce = 3207966;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xbe3ccf25f79bc3c8832bde8c0081cc28c88736f91ae9648879af9ae31a470ef8"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testseed1.zija.icu", "testseed1.zija.icu"));
        vSeeds.push_back(CDNSSeedData("testseed2.zija.icu", "testseed2.zija.icu"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xdf;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = bnProofOfStakeLimit = CBigNum(~uint256(0) >> 1);
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1532552400;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 3207966;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0xbe3ccf25f79bc3c8832bde8c0081cc28c88736f91ae9648879af9ae31a470ef8"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
