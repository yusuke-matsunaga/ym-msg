#ifndef YM_MSGHANDLER_H
#define YM_MSGHANDLER_H

/// @file ym/MsgHandler.h
/// @brief MsgHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "ym_config.h"
#include "ym/MsgType.h"


BEGIN_NAMESPACE_YM

class MsgMgrImpl;

//////////////////////////////////////////////////////////////////////
/// @class MsgHandler MsgHandler.h "ym/MsgHandler.h"
/// @ingroup ym-msg
/// @brief メッセージハンドラを表す基底クラス
//////////////////////////////////////////////////////////////////////
class MsgHandler
{
  friend class MsgMgrImpl;

public:

  /// @brief コンストラクタ
  /// @param[in] mask メッセージマスク
  MsgHandler(MsgBitMask mask = kMsgMaskAll);

  /// @brief デストラクタ
  ///
  /// 登録されていたら削除する．
  virtual
  ~MsgHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // メッセージマスクの管理
  //////////////////////////////////////////////////////////////////////

  /// @brief メッセージマスクの設定
  void
  set_mask(MsgBitMask mask);

  /// @brief メッセージマスクの取得
  MsgBitMask
  mask() const;

  /// @brief マスクの付加
  /// @param[in] type 付加するメッセージタイプ
  ///
  /// type はビットマスクではない．
  void
  add_mask(MsgType type);

  /// @brief マスクの削除
  /// @param[in] type 削除するメッセージタイプ
  ///
  /// type はビットマスクではない．
  void
  delete_mask(MsgType type);


public:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスが実装する仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief メッセージが登録されるたびに呼ばれる仮想関数
  /// @param[in] src_file この関数を読んでいるソースファイル名
  /// @param[in] src_line この関数を読んでいるソースの行番号
  /// @param[in] type メッセージの種類
  /// @param[in] label メッセージラベル
  /// @param[in] body メッセージ本文
  virtual
  void
  put_msg(const char* src_file,
	  int src_line,
	  MsgType type,
	  const char* label,
	  const char* body) = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられるメンバ関数
  //////////////////////////////////////////////////////////////////////

  /// @brief メッセージが登録されるたびに呼ばれる仮想関数
  /// @param[in] src_file この関数を読んでいるソースファイル名
  /// @param[in] src_line この関数を読んでいるソースの行番号
  /// @param[in] loc ファイル位置
  /// @param[in] type メッセージの種類
  /// @param[in] label メッセージラベル
  /// @param[in] body メッセージ本文
  ///
  /// メッセージタイプを調べて適合していれば put_msg() を呼ぶ．
  void
  event_proc(const char* src_file,
	     int src_line,
	     MsgType type,
	     const char* label,
	     const char* body);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // メッセージマスク
  MsgBitMask mMask;

  // リストの削除に用いる反復子
  list<MsgHandler*>::iterator mIter;

  // このオブジェクトを持っている親クラス
  MsgMgrImpl* mMgr;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief メッセージマスクの設定
inline
void
MsgHandler::set_mask(MsgBitMask mask)
{
  mMask = mask;
}

// @brief メッセージマスクの取得
inline
MsgBitMask
MsgHandler::mask() const
{
  return mMask;
}

// @brief マスクの付加
// @param[in] type 付加するメッセージタイプ
//
// type はビットマスクではない．
inline
void
MsgHandler::add_mask(MsgType type)
{
  mMask |= conv2bitmask(type);
}

// @brief マスクの削除
// @param[in] type 削除するメッセージタイプ
//
// type はビットマスクではない．
inline
void
MsgHandler::delete_mask(MsgType type)
{
  mMask &= ~(conv2bitmask(type));
}


END_NAMESPACE_YM

#endif // YM_MSGHANDLER_H
