# lossless伸長処理時間

**単位=ms**
## Mono8 Width=5120, Height=5120

### 実装 v0.0.3
<details>
<summary>Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz </summary>
  
### 測定日 : 2022/4/5
### 測定Machine
* CPU : Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz   3.70 GHz
* Memory : 32.0 GB


|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |166.622 |45.055  |32.287|25.401| 26.659
|2  |162.94    |39.417   |23.477|18.489|18.639
|3  |164.098    |41.785   |22.234|20.333|16.246
|3  |161.732    |40.224   |24.763|25.166|17.110
|3  |161.982    |44.759   |32.435|25.975|18.194

v0.0.3から実際の処理に近づけるためDeCompressをループさせて測定
  
  
https://github.com/jai-rd/lossless_compression/releases/tag/v0.0.3  
https://github.com/jai-rd/lossless_compression/issues/21
</details>

<details>
<summary>AMD Ryzen 7 5800X 8-Core Processor 3.80 GHz </summary>
  
### 測定日 : 2022/4/5
### 測定Machine
* CPU : AMD Ryzen 7 5800X 8-Core Processor 3.80 GHz
* Memory : 32.0 GB


|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |131.084 |33.773  |22.937|18.969| 20.294
|2  |134.844    |33.626   |16.464|13.970|13.760
|3  |136.834    |44.443   |17.086|13.958|13.908
|3  |114.772    |35.849   |18.396|13.890|14.019
|3  |114.440    |28.428   |21.030|14.253|15.653

v0.0.3から実際の処理に近づけるためDeCompressをループさせて測定
</details>

### 実装 v0.0.2
<details>
<summary>Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz </summary>
  
### 測定日 : 2022/4/4
### 測定Machine
* CPU : Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz   3.70 GHz
* Memory : 32.0 GB

|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |165.10 |43.55  |25.61|21.30| 20.86
|2  |166.71    |45.98   |25.60|21.57|20.03
|3  |165.08    |43.74   |25.45|20.83|19.64
  
https://github.com/jai-rd/lossless_compression/releases/tag/v0.0.2  
https://github.com/jai-rd/lossless_compression/issues/17
</details>


<details>
<summary>AMD Ryzen 7 5800X 8-Core Processor 3.80 GHz </summary>
  
### 測定日 : 2022/4/5
### 測定Machine
* CPU : AMD Ryzen 7 5800X 8-Core Processor 3.80 GHz
* Memory : 32.0 GB

|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |115.96 |30.86  |20.25|15.7| 15.37
|2  |116.16 |30.19   |19.02|15.85|15.07
|3  |116.63    |33.97   |19.85|17.79|15.73
</details>

### 実装 v0.0.1
<details>
<summary>Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz </summary>
  
### 測定日 : 2022/4/4
### 測定Machine
* CPU : Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz   3.70 GHz
* Memory : 32.0 GB

|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |217.42 |55.98  |30.59|25.54| 23.15
|2  |217.52    |56.76   |29.62|25.06|23.44
|3  |216.89    |56.66   |32.42|25.21|23.44
  
https://github.com/jai-rd/lossless_compression/releases/tag/v0.0.1  
https://github.com/jai-rd/lossless_compression/issues/15
</details>


### first実装
<details>
<summary>Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz </summary>
  
### 測定日 : 2022/4/4
### 測定Machine
* CPU : Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz   3.70 GHz
* Memory : 32.0 GB

|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16|ThreadNum=20
|--|--|--|--|--|--|
|1  |213.03 |55.75  |30.23|24.80| 23.61
|2  |240.02    |130.94   |32.86|26.03|23.05
|3  |238.63    |56.76   |32.49|24.86|23.75
  
測定コードは2021/7/28同等処理
</details>


<details>
<summary>Ryzen3700</summary>

### 測定日 : 2021/7/28頃
### 測定Machine
* CPU : Ryzen3700
* Memory : 32GB

|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |124 |34  |20|17
|2  |124    |36   |20|16
|3  |124    |32   |20|17

</details>




