Marketcoin
================================

http://www.qubitmarketcoin.com

Copyright (c) 2009-2014 Bitcoin Developers

Copyright (c) 2011-2014 Litecoin Developers

Copyright (c) 2018 Marketcoin Developers

What is Marketcoin?
----------------

Marketcoin (XMQ) – Mine on CPU only

Everyone can mine it !!! with CPU, 4GB RAM, 2 chores 1.5GHz

NO: GPU, NO ASIC miners, NO farms of computers, only CPU mining like you and I

Marketcoin is a lite version of Bitcoin using a special algorithm to only allow CPU mining and stop ASIC, GPU and all kind of farms to take advantage of expensive resources. Plus it stops the madness of electricity consumption to mine crypto.

26 million max no coins
10 coins reward for mining a block, to avoid pump and dumps
No halving, reward is 10 coins for mining a block up to the max no of coins
5.6 minutes, Average time to mine a block on a CPU with 4 GB RAM
Scrypt as a proof-of-work algorithm
CPU mining only, ASIC and farms will waste power with no benefit

Future plans
--------------
Privacy and secret of transactions originator
---------------------------------------------
Another issue with the current crypto is the fact that transactions can be tracked and we can find the participant wallets’ IP addresses. We will start by removing the IP addresses from all the logs, and implement a simple channel of communication between wallets and the blockchain and between blockchains without disclosing the IP addresses.

Mining on mobile
-----------------

This will be the next step in designing mining to work on mobile devices, with very low CPU power. ASIC and Farms will have no advantage over mobile phones, being a complete waste of electricity.
For more information, as well as an immediately useable, binary version of the Marketcoin client sofware, see http://www.qubitmarketcoin.com.

License
-------

Marketcoin is released under the terms of the MIT license. See `COPYING` for more information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Marketcoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch submitter will be asked to start a discussion with the devs and community.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/qubitmarketcoin/marketcoin/tags) are created
regularly to indicate new official, stable release versions of Marketcoin.

Testing
-------

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./marketcoin-qt_test

github
git clone git@github.com:qubitmarketcoin/marketcoin.git

