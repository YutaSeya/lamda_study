#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

/**
 * @class list process
 *
 */
class SECDStack {
 private:
  std::list<std::string> l;

 public:
  /**
   * @brief コンストラクタ
   */
  SECDStack() {}

  /**
   * @brief デストラクタ
   */
  ~SECDStack() {}

  /**
   * @brief listの内容がemptyかどうか
   * @fn null
   * @return 1: empty 0: not empty
   */
  bool isNull() { return l.empty(); }

  /**
   * @brief 引数を唯一の要素とするリストを返す関数
   * @fn unitlist
   */

  /**
   * @brief リストの先頭要素を返す関数
   * @fn h
   */
  std::string getHead() { return l.front(); }

  /**
   * @brief リストの先頭要素を取り除いた残りのリスト
   * @fn tl
   */
  std::list<std::string> getRemoveFrontList() {
    std::list<std::string> x;
    if (isNull()) return l;
    for (auto it = l.begin(); it != l.end(); it++) {
      x.push_back(*it);
    }
    x.pop_front();
    return x;
  }

  /**
   * @brief リストの先頭要素を返す関数
   * @fn 1st
   */
  std::string getListFirst() { return l.front(); }

  /**
   * @brief リストの先頭要素を返す関数
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
   * @brief リストの後ろにデータを入れる
   */
  void inputListBack(std::string data) { l.push_back(data); }

  /**
   * @brief リストの先頭要素を削除
   */
  void deleteListHead() { l.pop_front(); }

  /**
   * @brief リストの要素を表示
   */
  void printList(std::string title) {
    std::vector<std::string> x;
    for (auto it = l.begin(); it != l.end(); it++) {
      x.push_back(*it);
    }

    std::cout << title;
    std::cout << " : [ ";

    for (size_t i = 0; i < x.size(); i++) {
      if (i == x.size() - 1)
        std::cout << x[i];
      else
        std::cout << x[i] << ", ";
    }

    std::cout << " ]" << std::endl;
  }
};
