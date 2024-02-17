# gob_adapter

[English](README.md)

## 概要
既存クラスの公開関数を組み合わせた独自関数を、あたかも既存クラスのクラス関数のように使用する為のライブラリです。  
C++11 以降の環境下で使用できます。  
以下の特徴と制限があります。

### 特徴
- 独自関数をカプセル化できる。
- 既存クラスのソースコードに影響は与えない
- "has-a" による実装なので既存クラスに副作用が起こらない (既存クラス継承による諸々の問題が発生しない)
- 矢印演算子とドット演算子が混在するので、一見分かりづらいかもしれません  
(但し既存のクラス関数と独自関数のどちらを呼び出しているかは明確になります)
- 既存クラスの内部変更に対してこちらが受ける影響度が少ない

### 制限
- 継承ではないので既存クラスの公開関数しか使用できない

## 導入
環境によって適切な方法でインストールしてください
* git clone や Zip ダウンロードからの展開
* platformio.ini
```ini
lib_deps = https://github.com/GOB52/gob_adapter.git
```
## 使用方法

```cpp
#include <gob_adapter.hpp>

// Original class
class Original
{
  public:
    explicit Original(int v) : _v(v) {}
    int value() const { return _v; }
  private:
    int _v{};
};

// Extened class
// Add function to return squared value
class Extended : public goblib::plugin::Adapter<Original>
{
    using goblib::plugin::Adapter<Original>::_cls;
  public:
    using goblib::plugin::Adapter<Original>::Adapter; // for constructor

    int square() const { return _cls->value() * _cls->value(); }
};

Original org(52);
Extended  extended(org);

void foo()
{
    printf("Value:%d\nSquare:%d\n",
           extended->value(), // Call Original::value()
           extended.square()  // Call Extended::square()
           );

    Extended* ep = &extended;
    printf("Value:%d\nSquare:%d\n%d\n",
           (*ep)->value(), // Call Original::value()
           ep->square(),   // Call Extended::square()
           (*ep).square()  // Call Extended::square()
           );
}
```

## 例

- [simple](examples/simple) シンプルな例
- [M5GFX](examples/M5GFX) LovyanGFX に自作描画関数を加える例

