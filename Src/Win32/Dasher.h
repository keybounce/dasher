#pragma once



#include "../DasherCore/Win32/DasherInterface.h"
#include "Common/WinHelper.h"
#include "Common/WinWrap.h"
#include "DasherWindow.h"
#include "Widgets/Canvas.h"
#include "Widgets/Slidebar.h"
#include "EditWrapper.h"
#include "../DasherCore/UserLog.h"

extern CONST UINT WM_DASHER_EVENT;
#define _WM_DASHER_EVENT (LPCWSTR)"wm_dasher_event"

extern CONST UINT WM_DASHER_FOCUS;
#define _WM_DASHER_FOCUS (LPCWSTR)"wm_dasher_focus"

namespace Dasher {
  class CDasher;
} 

class Dasher::CDasher : public CDasherInterface {
public:
  CDasher(HWND Parent);
  ~CDasher(void);

  // The following functions will not be part of the final interface

  CCanvas *GetCanvas() {
    return m_pCanvas;
  }

  CSlidebar *GetSlidebar() {
    return m_pSlidebar;
  }

  void SetEdit(CDashEditbox * pEdit);

  void ExternalEventHandler(Dasher::CEvent *pEvent);

  CUserLog*     GetUserLogPtr();

  virtual void WriteTrainFile(const std::string &strNewText);


private:

  void                    AddFiles(Tstring Alphabets, Tstring Colours, CDasherInterface * Interface);
  bool                    GetWindowSize(int* pTop, int* pLeft, int* pBottom, int* pRight);
  static DWORD WINAPI     WorkerThread(LPVOID lpParam);     // Spins around and sends WM_DASHER_TIMER message
  void                    ShutdownWorkerThread();           // Called when we want the worker thread to stop
  void                    OnTimer();                        // Does the periodic work

  CCanvas *m_pCanvas;
  CSlidebar *m_pSlidebar;
  CEditWrapper *m_pEditWrapper;

  HANDLE m_workerThread;        // Handle to our worker thread that periodically checks on user's activities
  bool m_bWorkerShutdown;       // Set to true when the worker should terminate
    
  HWND m_hParent;

};