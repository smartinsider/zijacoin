// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"
#include "main.h"
#include "uint256.h"
#include <stdint.h>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

	
	
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (50,     uint256("0x104ce025b4bab89d852190b2cb45dcb751587519ce63e1e3e9d5d9f42d873cf6"))
        (250,    uint256("0xf28769e7e4fee7095495b3f18e2daf29669c896786d01cbce0d56227dfdd8b39"))
        (3333,   uint256("0xd6be96b9a4b7a27cc18067346ae43b5194c282eb3dd9f08c1987220f184cae45"))
        (5555,   uint256("0x0ce097e4c579a41e98d61bb8bd88027780b71be98f22cff0dc304e5fdb2fbd07"))
        (8080,   uint256("0x79ac9080b65e3723461a5d963e882a1aee55bf35050460ab72bc4bd9cf1b29ac"))
        (12010,  uint256("0x0818a0c036c4d7d3e8ee1704b4a511e32ee5dc03bf375b1ce774fa37488ea706"))
        (19000,  uint256("0x276a4a5b0759346a8e13181ef4c4eb6944895ef1432ef467a72e36c8ff6f109a"))
        (20800,  uint256("0xd5ee24a929796614f2b918fb55546de5aa610dd4fd8edd45bbfd0ffbef355018"))
        (20801,  uint256("0x7e5677ee677a953de6ec6eede219f12f8bb97f8f96a1b29377ccb379c45408fe"))
        (20802,  uint256("0x80d85806ad5f697859db2352b1c89f76502b393c0235d10f0d1b9452e7b15877"))
        (20803,  uint256("0x6692e704361f8d265dbfa5f58bd9e0c7f8e3f3c4c2c7023ec24ac22061ee5ac5"))
        (20804,  uint256("0x91a9581bbe5b30ce23c1038aba45335f41e39cdf2f7683fc3eff2e6639c8b910"))
        (20805,  uint256("0x3543ba217bb971c88478a50920e4604166a272529cbda618fe0d52821d27a728"))
        (20806,  uint256("0x2cfa57ae72a1ff6cff765736f54cbc642004bc425ba7d50a6d0c996faae24915"))
        (20807,  uint256("0x0003ad2767426809ad88ee360114e46e33fdd9b7d1bfacfefa97044269214617"))
        (20808,  uint256("0x4ac66291835f6f3629f1c2da33985f8a7278d8901820d4e055a72f5d8e32c9d4"))
        (20809,  uint256("0xaf4e7f686e73eb34e8d13d0206dec4b2a98e63d9c05f3fc0af524eb61ed7e7fb"))
        (20810,  uint256("0xcf20eab4be9b165668108bb9d8c376968e4fcbd8820e9b8894ec99f6b97f6d4e"))
        (20811,  uint256("0x942f07d591f3af673b7485379e77ff9f63b629cd3a255e38c3e857f42e47d3bb"))	    
        (20812,  uint256("0xf10e79d97fb69a194b83b4071193b41c5e0c2b5d132528821c65dfaed3f7672d"))
        (20813,  uint256("0x0818a0c036c4d7d3e8ee1704b4a511e32ee5dc03bf375b1ce774fa37488ea706"))
        (20814,  uint256("0x6e54827eeaee387471a18729089bc8ceb203c08e5d57e182235c672b54cd8f62"))
        (23392,  uint256("0xd92e275d760b475788af7c9c1ec467b932f692305cee23e4a2fffe5c8b583e30"));
    static const CCheckpointData data = {
        &mapCheckpoints,
        1537512351, // * UNIX timestamp of last checkpoint block
        34819,        // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        50000.0      // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (      0, uint256("0xbe3ccf25f79bc3c8832bde8c0081cc28c88736f91ae9648879af9ae31a470ef8"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1456668199, // * UNIX timestamp of last checkpoint block
        322625,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1401051600,
        1,
        10
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
