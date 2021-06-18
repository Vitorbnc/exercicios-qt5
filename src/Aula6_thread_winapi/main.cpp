#define WIN32_LEAN_AND_MEAN // Só os .h mais básicos serão incluídos.
#include <iostream>
#include <windows.h>
#include <process.h>
typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(LPVOID lpThreadParameter);
typedef unsigned *PBEGINTHREADEX_THREADID;
// This ThreadObject is created by a thread that wants to start another
// thread. All public member functions except ThreadFunc() are called by
// that original thread. The virtual function ThreadMemberFunc() is the
// start of the new thread.
class ThreadObject
{
public:
ThreadObject(); // Construtor
void StartThread();
void WaitForExit();
static DWORD WINAPI ThreadFunc(LPVOID param);
void SetKillThread(bool kill);
bool GetKillThread();
protected:
virtual DWORD ThreadMemberFunc();
HANDLE m_hThread; // Handle para thread criada
DWORD m_ThreadId; // Identificador da thread
bool KillThread;
};
ThreadObject::ThreadObject() // Inicializa membros privados da classe
{
this->m_hThread = NULL;
this->m_ThreadId = 0;
this->KillThread = false;
}
void ThreadObject::StartThread()
{
m_hThread = (HANDLE)_beginthreadex(NULL, 0,
(PBEGINTHREADEX_THREADFUNC) ThreadObject::ThreadFunc,
(LPVOID)this, // passa pointer para objeto como parâmetro
0, (PBEGINTHREADEX_THREADID) &m_ThreadId );
if (m_hThread) {
std::cout<< "Thread launched\n";
}
}
void ThreadObject::WaitForExit() // Espera fim da thread
{
WaitForSingleObject(m_hThread, INFINITE);
CloseHandle(m_hThread);
}
void ThreadObject::SetKillThread(bool kill) {
this->KillThread = kill;
}
bool ThreadObject::GetKillThread() {
return this->KillThread;
}
// This is a static member function. Unlike C static functions, you only
// place the static declaration on the function declaration in the class, not
// on its implementation. Static member functions have no "this" pointer, but
// do have access rights.
DWORD WINAPI ThreadObject::ThreadFunc(LPVOID param) {
// Use the param as the address of the object
ThreadObject* pto = (ThreadObject*)param;
// Call the member function. Since we have a proper object pointer,
// even virtual functions will be called properly.
return pto->ThreadMemberFunc();
}
// This above function ThreadObject::ThreadFunc() calls this function after the
// thread starts up.
DWORD ThreadObject::ThreadMemberFunc()
// Função que desempenhará as funções da thread
{
// Do something useful ...
while(!this->GetKillThread())
{
std::cout << ".";
Sleep(1000);
}
return 0;
}
void main()
{
ThreadObject obj;
obj.StartThread(); // Cria thread
Sleep(10000);
obj.SetKillThread(true);
obj.WaitForExit(); // Espera fim da thread
}