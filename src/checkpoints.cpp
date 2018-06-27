// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            (  0, uint256("0x1ae2d2c9dea37db9a29da7a6e90c7209e3ea14072b635d5881f1b5c5031e8193"))
			( 1,uint256("0x8333ce8a62d0a33cab30deff388c6b6ff0a594cf06b2f615d4317b52affc457d"))
			( 2,uint256("0xfb362dbd36e045106ea6fa80b2b7ca3efa621d603e36c4783e1c8e8c981b4fdd"))
			( 3,uint256("0x8c886fd4f1a9eef5013f653299ee363eb1778e128c0d280bea7d01975dc84043"))
			( 4,uint256("0x47c73f632cd7ccee4d9024c7bd9705344ec6c880a9ee42d97d2d51d8f90bc1fc"))
			( 5,uint256("0x3998a138cd469049f986d6bc1ca0f26ebf0f4a5121994e5c402ba234f003d174"))
			( 6,uint256("0xe9aa5942e33f3011cbcf0569a22f14f64bd6a9f35ea7b80a183ca89b6b3a1bce"))
			( 7,uint256("0x3b6a6803818374f7b32464a7e5f9688ad2806878e9131d2bce695a3594fc7263"))
			( 8,uint256("0xd22d81a195109cdc433531049a8610da12eac28c37efe96a0c8e5373f99de634"))
			( 9,uint256("0x55f9606929345e36cf11609dc8fba56e751253227c72e25528f884daf8397991"))
			(10,uint256("0xad5b94555fc510923d95f3edcef34246c2bd8d965e7d3db7b72d99ec0ea8458b"))
			(11,uint256("0xae206f97786d03c69fa0f9a2b33f4c4ce5efde4d7c8b8f5909329fe20a21aeb7"))
			(12,uint256("0x928bb0533c0b5b5efb3698ff5c5f988c2886bfa65e93ff6330d88e517f030a61"))
			(91,uint256("0xf3709a2c730a2270b8e1f663bd1bae2eb13ec56b844c2775b38667cd3da38b53"))
	;
    static const CCheckpointData data = {
        &mapCheckpoints,
		1530089987, // * UNIX timestamp of last checkpoint block
        94,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        150.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   0, uint256("0xb4c132e5e9a6792ab421dac58660dab47592bb1c86c99ac781b6f9814de282c0"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
		1530000229,
        0,
        1.0
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
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
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
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
