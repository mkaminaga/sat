SATライブラリ リファレンス
====
STAライブラリに含まれるデータや関数の扱い方についてまとめる。

構造体の説明
----

TLE構造体 `sat::TLEData`
------
これについては[mkaminaga/tle](https://github.com/mkaminaga/TLE)の`README.md`を参照すること。

衛星構造体 `struct SatData`
------
人工衛星のデータをまとめた構造体である。<br>
軌道計算の入力と出力はこの構造体を通して行う。

|データ型|変数名|説明|単位|
|---|---|---|---|
|int|error|エラーステータス|0:正常<br>1:ニュートン法に失敗|
|double|jdepoch|TELの元期|JD（ユリウス日）|
|double|argpo|TLEの近地点引数|rad|
|double|inclo|TLEの軌道傾斜角|rad|
|double|nodeo|TLEの昇交点赤経|rad|
|double|ecco|TLEの離心率|なし|
|double|mo|TLEの平均近点角|rev|
|double|no|TLEの平均運動|rev/day|
|double|ndoto|TLEの平均運動変化率（一階微分）|rev/day^2|
|double|nddoto|TLEの平均運動変化率（二階微分）|rev/day^3|
|double|ao|TLEの時点での軌道長半径|m|
|double|argp1|J2項による近地点引数への永年変動|rad/day|
|double|node1|J2項による昇交点赤経への永年変動|rad/day|
|double|jd|計算日|JD|
|double|m|計算日の平均近点角|rev|
|double|n|計算日の平均運動|rev/day|
|double|argp|計算日の近地点引数|rad|
|double|node|計算日の昇交点赤経|rad|
|double|e|計算日の離心近点角|rad|
|Point3|u|軌道面での衛星座標|m|
|Point3|r|ECI座標系での衛星座標|m|
|Point3|p|ECEF座標系での衛星座標|m|

観測者位置構造体 `sat::WGS84Point`
------
WGS-84に準拠し観測者の位置を指定する構造体である。<br>

|データ型|変数名|説明|単位|
|---|---|---|---|
|double|lambda|観測者の経度|rad|
|double|phi|観測者の緯度|rad|
|double|m|観測者の海抜|m|

衛星可視位置構造体 `sat::WiewedPoint`
------
地平座標系における衛星の位置が格納される構造体である。<br>

|データ型|変数名|説明|単位|
|---|---|---|---|
|double|rho|観測者から衛星までの距離|m|
|double|az|衛星の方位|rad|
|double|el|衛星の仰角|rad|

日時構造体 `sat::Calendar`
------
グレゴリオ暦で表した日時である。<br>
秒よりも細かい値は、秒の小数点以下に格納すること。

|データ型|変数名|説明|
|---|---|---|
|int|year|年|
|int|mon|月|
|int|day|日|
|int|hour|時|
|int|min|分|
|double|sec|秒|

関数の説明
----

```
bool sat::InitSat(const TLEData& tle, SatData* sat);
```

`sat::TLEData`で指定されたTLEから情報を抜き取り、`sat::SatData`に情報をセットする。TLEの元期における軌道計算を同時に行う。`sat::SatData`をユーザー側で複数用意することで、ライブラリ自体を毎回初期化せずに複数の衛星のデータを同時に扱うことができる。
<br>

```
bool sat::GetSatPos(double jd, SatData* sat);
```

与えられたJDにおける衛星の軌道情報を計算する。第二引数の`sat::SatData`は事前に`sat::InitSat`関数で対応する`sat::TLEData`により初期化する必要がある。
<br>

```
void sat::ECIToECEF(const Point3& r, double jd, Point3* p);
```

ECI座標系で与えられた座標`r`を、指定されたユリウス日`jd`におけるECEF座標系での座標`p`に変換する。
<br>

```
void sat::WGS84ToECEF(const WGS84Point& w, Point3* p);
```

WGS-84の表現で与えられた位置`w`を、ECEF座標系での座標`p`に変換する。
<br>

```
void sat::ViewSat(const WGS84Point& w, const Point3& ps, WiewedPoint* q);
```

WGS-84の表現で与えられた観測点`w`、ECEF座標系での衛星座標`p`を受け取り、観測点での地平座標系（距離、方位、仰角）での衛星座標を返す。
<br>

```
void sat::DaysToMDHMS(int year, double days, int* mon, int* day, int* hour,
                      int* min, double* sec);
```

年`year`と年内の通日`days`で表された時刻から、対応するグレゴリオ暦の月`mon`、日`day`、時`hour`、分`min`、秒`sec`を求める。
<br>

```
double sat::ToJulianDay(const Calendar& cal);
```

グレゴリオ暦での日時`sat::Calendar`を対応するユリウス日に変換する。
<br>

```
void sat::ToCalendar(double jd, Calendar* cal);
```

ユリウス日`jd`を対応するグレゴリオ暦での日時`sat::Calendar`をに変換する。
<br>


```
double sat::GetGSTime(double jd);
```

与えられたユリウス日`jd`におけるグリニッジ恒星時(rad)を返す。
<br>
