# Test code for transaction calculation
this is a simple implementation of Transaction Calculation

## Description
input format: 
```
<timestamp>,<symbol>,<volume>,<price>
```
output format:
```
<symbol>,<max_timegap>,<trade_volume>,<avg_price>,<max_price>
```


## Run
please execute the following command:
```bash
cd your/path/to/test_code
g++ test.cpp
./a.out input.csv output.csv
```

