# FalconCalc
Roman Numeral Calculator

#### Master
[![wercker status](https://app.wercker.com/status/96f106f534fd8b0ba05d12b70bf19b95/s/master "wercker status")](https://app.wercker.com/project/bykey/96f106f534fd8b0ba05d12b70bf19b95)  
[![Coverage Status](https://coveralls.io/repos/github/StummeJ/FalconCalc/badge.svg?branch=master)](https://coveralls.io/github/StummeJ/FalconCalc?branch=master)

#### Develop
[![wercker status](https://app.wercker.com/status/96f106f534fd8b0ba05d12b70bf19b95/s/develop "wercker status")](https://app.wercker.com/project/bykey/96f106f534fd8b0ba05d12b70bf19b95)  
[![Coverage Status](https://coveralls.io/repos/github/StummeJ/FalconCalc/badge.svg?branch=develop)](https://coveralls.io/github/StummeJ/FalconCalc?branch=develop)

###Building and Running:
#####Install needed debian packages:
```shell
apt-get install -y cmake pkg-config gperf gcc-multilib libc6-dev build-essential
```
#####Build source:
```shell
cmake .
make
```
#####Run tests:
```shell
tests\TestFalconCalc
```
#####Build coverage report:
```shell
cmake -DCMAKE_BUILD_TYPE=Debug
make FalconCalc_cov
```
