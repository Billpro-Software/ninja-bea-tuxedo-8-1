//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// ShutdownManager.java
//
// Class to help the main and the servant in the notification java
// samples coordinate shutting down the server.
//
// In these samples, the main creates a ShutdownManager and gives
// it to the servant.  Then the main calls "wait_for_shutdown" on
// the shutdown manager.  At this point, the main thread of control
// is blocked waiting.  When an event is delivered to the servant,
// the servant prints out the event and calls "shutdown" on the
// shutdown manager.  This causes the main thread to wake up
// and "wait_for_shutdown" to return.  After that, the main cleans
// up and exits.
//
// This class is needed since the Java ORB doesn't have orb->run
// and orb->shutdown calls (unlike the C++ ORB)

// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

class ShutdownManager
{
  // called by the servant that wants to tell the main to shutdown
  public synchronized void shutdown()
  {
    m_done = true;
    notifyAll();
  }

  // called by the main to wait to shutdown until the servant
  // calls shutdown
  public synchronized void wait_for_shutdown()
  {
    try {
      while (!m_done) {
          wait();
      }
    }
    catch (InterruptedException e) {}
  }

  private boolean m_done = false;
};
