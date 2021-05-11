#pragma once

#include <string>

class LambdaEquation {
 private:
 public:
  /**
   * @details コンストラクタ
   */
  LambdaEquation() {}

  /**
   * @details デストラクタ
   */
  ~LambdaEquation() {}

  /**
   * @details 引数が変数であるかどうかを判定する関数
   * @fn identifier
   */
  bool isIdentifier(std::string c) { return false; }

  /**
   * @details 引数がabstractionであるかどうかを判定する関数
   * @fn lambda exp
   */
  bool isLambdaExp(std::string c) { return false; }

  /**
   * @details abstractionを引数として束縛変数（𝜆𝑣.𝑀の𝑣）を抽出する関数
   * @fn bv
   */
  std::string extractionBondageVaraiable(std::string c) {
    std::string bv;
    return bv;
  }

  /**
   * @details abstractionを引数として本体部分（𝜆𝑣.M のM）を抽出する関数
   * @fn body
   */
  std::string extractionBodyVaraiable(std::string c) {
    std::string body;
    return body;
  }

  /**
   * @details この定義中で使われる構造closureを構築する関数
   * @fn constructclosure
   */
  std::string buildConstructclosure(std::string c) {
    std::string constructclosure;
    return constructclosure;
  }

  bool isClosure(std::string c) { return false; }
};