# FalconCalc
Roman Numeral Calculator

#### Master
[![wercker status](https://app.wercker.com/status/e6633599c0919117eb4c008694be4587/s/master "wercker status")](https://app.wercker.com/project/bykey/e6633599c0919117eb4c008694be4587)
[![Coverage Status](https://coveralls.io/repos/github/StummeJ/FalconCalc/badge.svg?branch=master&t=VzoO69)](https://coveralls.io/github/StummeJ/FalconCalc?branch=master)

#### Develop
[![wercker status](https://app.wercker.com/status/e6633599c0919117eb4c008694be4587/s/develop "wercker status")](https://app.wercker.com/project/bykey/e6633599c0919117eb4c008694be4587)
[![Coverage Status](https://coveralls.io/repos/github/StummeJ/FalconCalc/badge.svg?branch=develop&t=VzoO69)](https://coveralls.io/github/StummeJ/FalconCalc?branch=develop)

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
