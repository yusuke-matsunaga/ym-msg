
/// @file MsgHandler.cc
/// @brief MsgHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "ym/MsgHandler.h"
#include "ym/StreamMsgHandler.h"
#include "MsgMgrImpl.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
// クラス MsgHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
MsgHandler::MsgHandler(MsgBitMask mask) :
  mMask{mask}
{
}

// @brief デストラクタ
MsgHandler::~MsgHandler()
{
  if ( mMgr != nullptr ) {
    mMgr->unreg_handler(this);
  }
}

// @brief メッセージが登録されるたびに呼ばれる仮想関数
// @param[in] src_file この関数を読んでいるソースファイル名
// @param[in] src_line この関数を読んでいるソースの行番号
// @param[in] type メッセージの種類
// @param[in] label メッセージラベル
// @param[in] body メッセージ本文
void
MsgHandler::event_proc(const char* src_file,
		       int src_line,
		       MsgType type,
		       const char* label,
		       const char* body)
{
  MsgBitMask bit = conv2bitmask(type);
  if ( mMask & bit ) {
    put_msg(src_file, src_line, type, label, body);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス StreamMsgHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
StreamMsgHandler::StreamMsgHandler(ostream& stream) :
  mStream{stream}
{
}

// @brief デストラクタ
StreamMsgHandler::~StreamMsgHandler()
{
}

// @brief メッセージが登録されるたびに呼ばれる仮想関数
// @param[in] src_file この関数を読んでいるソースファイル名
// @param[in] src_line この関数を読んでいるソースの行番号
// @param[in] type メッセージの種類
// @param[in] label メッセージラベル
// @param[in] body メッセージ本文
void
StreamMsgHandler::put_msg(const char* src_file,
			  int src_line,
			  MsgType type,
			  const char* label,
			  const char* body)
{
  mStream << type << " [" << label << "]: " << body << endl;
}

END_NAMESPACE_YM
