#pragma once
#include <iostream>
#include <list>
#include <string>

/**
 * @class list process
 *
 */
class SECDStack {
 private:
  std::list<std::string> l;

 public:
  /**
   * @details コンストラクタ
   */
  SECDStack() {}

  /**
   * @details デストラクタ
   */
  ~SECDStack() {}

  /**
   * @details listの内容がemptyかどうか
   * @fn null
   * @return 1: empty 0: not empty
   */
  bool isNull() { return l.empty(); }

  /**
   * @details 引数を唯一の要素とするリストを返す関数
   * @fn unitlist
   */

  /**
   * @details リストの先頭要素を返す関数
   * @fn h
   */
  std::string getHead() { return l.front(); }

  /**
   * @details リストの先頭要素を取り除いた残りのリスト
   * @fn tl
   */
  std::list<std::string> getRemoveFrontList() {
    std::list<std::string> x;
    for (auto it = l.begin(); it != l.end(); it++) {
      x.push_back(*it);
    }
    x.pop_front();
    return x;
  }

  /**
   * @details リストの先頭要素を返す関数
   * @fn 1st
   */
  std::string getListFirst() { return l.front(); }

  /**
   * @details リストの先頭要素を返す関数
   * @fn 2nd
   */
  std::string getListSecond() {
    std::list<std::string> x;
    for (auto it = l.begin(); it != l.end(); it++) {
      x.push_back(*it);
    }
    x.pop_front();
    return x.front();
  }

  /**
   * @details リストの後ろにデータを入れる
   */
  void inputListBack(std::string data) { l.push_back(data); }
};
