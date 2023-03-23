# hdd_boot
Boot from HDD for PC-9801(1st)

## 説明
PC-9801初代でフロッピーディスク(FD-IPLware)を用い、ハードディスクから起動させる。

## コンパイル方法
Makefile参照

## 動作環境

### OS
OS起動前のFD-IPLware<br>
※FD-IPLwareについてはこちらを使用させていただきました。<br>
http://hp.vector.co.jp/authors/VA012947/index.html<br>
<br>
MS-DOS5.0/6.2

### 確認環境
NEC PC-9801初代<br>
SASI:PC-9801-27、変換番長PRO<br>
SCSI:PC-9801-55L、変換番長PRO<br>

## 使用方法
* 各モジュールをビルドし、FD-IPLwareとしてフロッピーディスクに書き込む。<br>
例：<br>
<pre>B:\>IPLWMKFD FDBOOT.BIN</pre>
<br>
* フロッピーディスクから起動すると、ブート可能なハードディスクからOSが読み込まれる。<br>
※元々のFD-IPLwareのドライブ選択の機能は使用しない。

## 詳細

### fdboot.bin
インストールFDからインストールする場合に、ハードディスクを認識させておきたいときに使用する。<br>
<br>
処理順
* SCSI ROM初期化
* SASI ROM初期化
* FDドライブ選択＆FDブート

※SASIにBOOT可のドライブがある場合は、SASI ROMを初期化すると自動的にブートしてしまうため、FDドライブ選択は現れない。

### hddboot.bin
SASIまたはSCSIハードディスクから起動する。<br>
SASIドライブを優先する。<br>
<br>
処理順
* SCSI ROM初期化
* SASI ROM初期化(＆ブート)
* SCSIブート

※SASIにBOOT可のドライブがある場合は、SASI ROMを初期化すると自動的にブートしてしまうため、SCSIハードディスクから起動したい場合は、SASIハードディスクの電源を切るか、BOOT不可に設定しておく。

### sasiboot.bin/scsiboot.bin
SASIまたはSCSI専用のモジュール。hddboot.binで代用可。
