# Object-Oriented Software Engineering hw3

+ Author: 黃柏瑄 (P78081528)

## OCSF (The Object Client-Server Framework)

+ Download link: https://www.site.uottawa.ca/school/research/lloseng/supportMaterial/source/llosengcode.zip

### Gained knowledge
+ Hook 的設計在框架上很重要，可以使得使用框架的開發者在相對應的時間點放入自己想要達到的程式邏輯。這在機器學習的框架上也可以看到用來測量時間或是將每次訓練結果暫存的 Hook。
+ 在非同步的應用下，利用例外 (Exception) 處理可以讓程式提高可讀性，而不用每個操作都去檢查是否成功。
+ 利用 `ConnectionToClient` 去服務個別 Client 可以減少在 Server 中處理訊息的邏輯，並讓後續的擴充及維護更容易。

### Source code

+ File `ocsf/client/AbstractClient.java`:

```java
// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package ocsf.client;

import java.io.*;
import java.net.*;
import java.util.*;

/**
* The <code> AbstractClient </code> contains all the
* methods necessary to set up the client side of a client-server
* architecture.  When a client is thus connected to the
* server, the two programs can then exchange <code> Object </code>
* instances.<p>
* 包含所有設定 client 所需的方法，當 client 連接 server 後兩個程式可以
* 交換 Object
*
* Method <code> handleMessageFromServer </code> must be defined by
* a concrete subclass. Several other hook methods may also be
* overriden.<p>
* handleMessageFromServer 必須在實體的子類別中定義。其他 hook 可能
* 需要被覆寫
*
* Several public service methods are provided to
* application that use this framework.<p>
* 一些公開的服務方法被使用這個框架的應用程式提供
*
* Project Name: OCSF (Object Client-Server Framework)<p>
*
* @author Dr. Robert Lagani&egrave;re
* @author Dr. Timothy C. Lethbridge
* @author Fran&ccedil;ois  B&eacutel;langer
* @author Paul Holden
* @version February 2001 (2.12)
*/
public abstract class AbstractClient implements Runnable
{

// INSTANCE VARIABLES ***********************************************

  /**
  * Sockets are used in the operating system as channels
  * of communication between two processes.
  * Sockets 是作業系統中兩個程序的溝通通道
  * @see java.net.Socket
  */
  private Socket clientSocket;

  /**
  * The stream to handle data going to the server.
  * 用於處理將傳送到 server 的資料流
  */
  private ObjectOutputStream output;

  /**
  * The stream to handle data from the server.
  * 用於處理來自 server 的資料流
  */
  private ObjectInputStream input;

  /**
  * The thread created to read data from the server.
  * 用來讀取來自 Server 資料的執行緒
  */
  private Thread clientReader;

  /**
  * Indicates if the thread is ready to stop.
  * Needed so that the loop in the run method knows when to stop
  * waiting for incoming messages.
  * 表示執行緒是否已經準備停止
  * 用來使 run 函式知道何時可以停止等待正在傳入的訊息
  */
  private boolean readyToStop= false;

  /**
  * The server's host name.
  */
  private String host;

  /**
  * The port number.
  */
  private int port;

// CONSTRUCTORS *****************************************************

  /**
   * Constructs the client.
   *
   * @param  host  the server's host name.
   * @param  port  the port number.
   */
  public AbstractClient(String host, int port)
  {
    // Initialize variables
    this.host = host;
    this.port = port;
  }

// INSTANCE METHODS *************************************************

  /**
   * Opens the connection with the server.
   * If the connection is already opened, this call has no effect.
   * 開啟與 Server 的連接，如果已經連上，則此函式的呼叫無效
   *
   * @exception IOException if an I/O error occurs when opening.
   */
  final public void openConnection() throws IOException
  {
    // Do not do anything if the connection is already open
    if(isConnected())
      return;

    //Create the sockets and the data streams
    //建立 Sockets 和資料傳輸流
    try
    {
      clientSocket= new Socket(host, port);
      output = new ObjectOutputStream(clientSocket.getOutputStream());
      input = new ObjectInputStream(clientSocket.getInputStream());
    }
    catch (IOException ex)
    // All three of the above must be closed when there is a failure
    // to create any of them
    // 如果上面產生的部分有失敗的情況時必須關閉他們
    {
      try
      {
        closeAll();
      }
      catch (Exception exc) { }

      throw ex; // Rethrow the exception.
    }

    clientReader = new Thread(this);  //Create the data reader thread
    readyToStop = false;
    clientReader.start();  //Start the thread
  }

  /**
   * Sends an object to the server. This is the only way that
   * methods should communicate with the server.
   * 傳送物件給 Server。這應該要是唯一與 Server 溝通的方法
   *
   * @param msg   The message to be sent.
   * @exception IOException if an I/O error occurs when sending
   */
  final public void sendToServer(Object msg) throws IOException
  {
    if (clientSocket == null || output == null)
      throw new SocketException("socket does not exist");

    output.writeObject(msg);
  }

  /**
   * Closes the connection to the server.
   *
   * @exception IOException if an I/O error occurs when closing.
   */
  final public void closeConnection() throws IOException
  {
    // Prevent the thread from looping any more
    readyToStop= true;

    try
    {
      closeAll();
    }
    finally
    {
      // Call the hook method
      connectionClosed();
    }
  }

// ACCESSING METHODS ------------------------------------------------

  /**
   * @return true if the client is connected.
   */
  final public boolean isConnected()
  {
    return clientReader!=null && clientReader.isAlive();
  }

  /**
   * @return the port number.
   */
  final public int getPort()
  {
    return port;
  }

  /**
   * Sets the server port number for the next connection.
   * The change in port only takes effect at the time of the
   * next call to openConnection().
   * 設置下一個連接的 port。
   * port 的更改只在下次呼叫 openConnection 時
   *
   * @param port the port number.
   */
  final public void setPort(int port)
  {
    this.port = port;
  }

  /**
   * @return the host name.
   */
  final public String getHost()
  {
    return host;
  }

  /**
   * Sets the server host for the next connection.
   * The change in host only takes effect at the time of the
   * next call to openConnection().
   * 設置下一個連接的主機名稱
   * 此變更僅會在下次呼叫 openConnection 時
   *
   * @param host the host name.
   */
  final public void setHost(String host)
  {
    this.host = host;
  }

  /**
   * returns the client's description.
   *
   * @return the client's Inet address.
   */
  final public InetAddress getInetAddress()
  {
    return clientSocket.getInetAddress();
  }

// RUN METHOD -------------------------------------------------------

  /**
   * Waits for messages from the server. When each arrives,
   * a call is made to <code>handleMessageFromServer()</code>.
   * Not to be explicitly called.
   * 等待來自 Server 的訊息。當訊息抵達時， handleMessageFromServer
   * 將不會被顯性的呼叫
   */
  final public void run()
  {
    connectionEstablished();

    // The message from the server
    Object msg;

    // Loop waiting for data

    try
    {
      while(!readyToStop)
      {
        // Get data from Server and send it to the handler
        // The thread waits indefinitely at the following
        // statement until something is received from the server
        // 從 Server 獲取資料並且發送到處理程序
        // 此執行緒將一直等待直到收到來自 Server 的訊息
        msg = input.readObject();

        // Concrete subclasses do what they want with the
        // msg by implementing the following method
        handleMessageFromServer(msg);
      }
    }
    catch (Exception exception)
    {
      if(!readyToStop)
      {
        try
        {
          closeAll();
        }
        catch (Exception ex) { }

        connectionException(exception);
      }
    }
    finally
    {
      clientReader = null;
    }
  }

// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

  /**
   * Hook method called after the connection has been closed.
   * The default implementation does nothing. The method
   * may be overridden by subclasses to perform special processing
   * such as cleaning up and terminating, or attempting to
   * reconnect.
   * 連接關閉後呼叫的 Hook 函式。
   * 預設不執行任何操作。此函式可以被子類別覆寫以執行特殊處理，例如清理、
   * 終止，或試圖重新連接
   */
  protected void connectionClosed() {}

  /**
   * Hook method called each time an exception is thrown by the
   * client's thread that is waiting for messages from the server.
   * The method may be overridden by subclasses.
   * 每當 Client 的執行緒在等待 Server 的訊息時拋出例外時會呼叫到的
   * Hook 函式。此方法可以被子類別覆寫。
   *
   * @param exception the exception raised.
   */
  protected void connectionException(Exception exception) {}

  /**
   * Hook method called after a connection has been established.
   * The default implementation does nothing.
   * It may be overridden by subclasses to do anything they wish.
   * 建立連接時呼叫的 Hook 函式。預設不執行任何操作。可以被子類別覆寫
   * 以執行他們想要的任何事
   */
  protected void connectionEstablished() {}

  /**
   * Handles a message sent from the server to this client.
   * This MUST be implemented by subclasses, who should respond to
   * messages.
   * 處理從 Server 送到此 Client 的訊息。此函式必須由子類別實作
   *
   * @param msg   the message sent.
   */
  protected abstract void handleMessageFromServer(Object msg);


// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

  /**
   * Closes all aspects of the connection to the server.
   * 關閉所有跟 Server 的連接
   *
   * @exception IOException if an I/O error occurs when closing.
   */
  private void closeAll() throws IOException
  {
    try
    {
      //Close the socket
      if (clientSocket != null)
        clientSocket.close();

      //Close the output stream
      if (output != null)
        output.close();

      //Close the input stream
      if (input != null)
        input.close();
    }
    finally
    {
      // Set the streams and the sockets to NULL no matter what
      // Doing so allows, but does not require, any finalizers
      // of these objects to reclaim system resources if and
      // when they are garbage collected.
      output = null;
      input = null;
      clientSocket = null;
    }
  }
}
// end of AbstractClient class
```

+ File `ocsf/server/AbstractServer.java`:

```java
// This file contains material supporting section 3.8 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package ocsf.server;

import java.net.*;
import java.util.*;
import java.io.*;

/**
* The <code> AbstractServer </code> class maintains a thread that waits
* for connection attempts from clients. When a connection attempt occurs
* it creates a new <code> ConnectionToClient </code> instance which
* runs as a thread. When a client is thus connected to the
* server, the two programs can then exchange <code> Object </code>
* instances.<p>
* AbstractServer 維護一個執行緒，該執行緒用來等待來自 Client 的連接。
* 嘗試進行連接時，此類別將產生一個新的 ConnectionToClient 實例，該實例
* 作為執行緒運行。這樣，當 Client 連接到 Server 後，兩方可以交換物件
*
* Method <code> handleMessageFromClient </code> must be defined by
* a concrete subclass. Several other hook methods may also be
* overridden.<p>
* handleMessageFromClient 函式必須由一個具體的子類別定義。其他幾種 Hook
* 也可以被覆寫。
*
* Several public service methods are provided to applications that use
* this framework, and several hook methods are also available<p>
*
* Project Name: OCSF (Object Client-Server Framework)<p>
*
* @author Dr Robert Lagani&egrave;re
* @author Dr Timothy C. Lethbridge
* @author Fran&ccedil;ois B&eacute;langer
* @author Paul Holden
* @version February 2001 (2.12)
* @see ocsf.server.ConnectionToClient
*/
public abstract class AbstractServer implements Runnable
{
  // INSTANCE VARIABLES *********************************************

  /**
   * The server socket: listens for clients who want to connect.
   * 用來聽取想連接的 Client
   */
  private ServerSocket serverSocket = null;

  /**
   * The connection listener thread.
   */
  private Thread connectionListener;

  /**
   * The port number
   */
  private int port;

  /**
   * The server timeout while for accepting connections.
   * After timing out, the server will check to see if a command to
   * stop the server has been issued; it not it will resume accepting
   * connections.
   * Set to half a second by default.
   * 接受連接時的超時設定。
   * 超時後，Server 將檢查是否發出了停止 Server 的命令，否則它將恢復接受連接
   */
  private int timeout = 500;

  /**
   * The maximum queue length; i.e. the maximum number of clients that
   * can be waiting to connect.
   * Set to 10 by default.
   * 可以等待連接的最大 Client 數量
   */
  private int backlog = 10;

  /**
   * The thread group associated with client threads. Each member of the
   * thread group is a <code> ConnectionToClient </code>.
   * 與 Client 連接的執行緒群組
   */
  private ThreadGroup clientThreadGroup;

  /**
   * Indicates if the listening thread is ready to stop.  Set to
   * false by default.
   * 指示聆聽的執行緒是否準備停止
   */
  private boolean readyToStop = false;


// CONSTRUCTOR ******************************************************

  /**
   * Constructs a new server.
   *
   * @param port the port number on which to listen.
   */
  public AbstractServer(int port)
  {
    this.port = port;

    this.clientThreadGroup =
      new ThreadGroup("ConnectionToClient threads")
      {
        // All uncaught exceptions in connection threads will
        // be sent to the clientException callback method.
        public void uncaughtException(
          Thread thread, Throwable exception)
        {
          clientException((ConnectionToClient)thread, exception);
        }
      };
  }


// INSTANCE METHODS *************************************************

  /**
   * Begins the thread that waits for new clients.
   * If the server is already in listening mode, this
   * call has no effect.
   * 開始等待新 Client 的執行緒
   *
   * @exception IOException if an I/O error occurs
   * when creating the server socket.
   */
  final public void listen() throws IOException
  {
    if (!isListening())
    {
      if (serverSocket == null)
      {
        serverSocket = new ServerSocket(getPort(), backlog);
      }

      serverSocket.setSoTimeout(timeout);
      readyToStop = false;
      connectionListener = new Thread(this);
      connectionListener.start();
    }
  }

  /**
   * Causes the server to stop accepting new connections.
   */
  final public void stopListening()
  {
    readyToStop = true;
  }

  /**
   * Closes the server socket and the connections with all clients.
   * Any exception thrown while closing a client is ignored.
   * If one wishes to catch these exceptions, then clients
   * should be individually closed before calling this method.
   * The method also stops listening if this thread is running.
   * If the server is already closed, this
   * call has no effect.
   * 關閉所有 Socket 以及與 Client 的連接
   *
   * @exception IOException if an I/O error occurs while
   * closing the server socket.
   */
  final synchronized public void close() throws IOException
  {
    if (serverSocket == null)
      return;
      stopListening();
    try
    {
      serverSocket.close();
    }
    finally
    {
      // Close the client sockets of the already connected clients
      Thread[] clientThreadList = getClientConnections();
      for (int i=0; i<clientThreadList.length; i++)
      {
         try
         {
           ((ConnectionToClient)clientThreadList[i]).close();
         }
         // Ignore all exceptions when closing clients.
         catch(Exception ex) {}
      }
      serverSocket = null;
      serverClosed();
    }
  }

  /**
   * Sends a message to every client connected to the server.
   * This is merely a utility; a subclass may want to do some checks
   * before actually sending messages to all clients.  This method
   * can be overridden, but if so it should still perform the general
   * function of sending to all clients, perhaps after some kind
   * of filtering is done. Any exception thrown while
   * sending the message to a particular client is ignored.
   * 向所有連接的 Client 發送訊息
   *
   * @param msg   Object The message to be sent
   */
  public void sendToAllClients(Object msg)
  {
    Thread[] clientThreadList = getClientConnections();

    for (int i=0; i<clientThreadList.length; i++)
    {
      try
      {
        ((ConnectionToClient)clientThreadList[i]).sendToClient(msg);
      }
      catch (Exception ex) {}
    }
  }


// ACCESSING METHODS ------------------------------------------------

  /**
   * Returns true if the server is ready to accept new clients.
   *
   * @return true if the server is listening.
   */
  final public boolean isListening()
  {
    return (connectionListener != null);
  }

  /**
   * Returns an array containing the existing
   * client connections. This can be used by
   * concrete subclasses to implement messages that do something with
   * each connection (e.g. kill it, send a message to it etc.).
   * Remember that after this array is obtained, some clients
   * in this might disconnect. New clients can also connect,
   * these later will not appear in the array.
   * 返回現有連接的所有 Client
   *
   * @return an array of <code>Thread</code> containing
   * <code>ConnectionToClient</code> instances.
   */
  synchronized final public Thread[] getClientConnections()
  {
    Thread[] clientThreadList = new
      Thread[clientThreadGroup.activeCount()];

    clientThreadGroup.enumerate(clientThreadList);

    return clientThreadList;
  }

  /**
   * Counts the number of clients currently connected.
   *
   * @return the number of clients currently connected.
   */
  final public int getNumberOfClients()
  {
    return clientThreadGroup.activeCount();
  }

  /**
   * Returns the port number.
   *
   * @return the port number.
   */
  final public int getPort()
  {
    return port;
  }

  /**
   * Sets the port number for the next connection.
   * The server must be closed and restarted for the port
   * change to be in effect.
   * 設置下一個連接的 port。必須關閉並重新啟動 Server，port 
   * 更動才能生效
   *
   * @param port the port number.
   */
  final public void setPort(int port)
  {
    this.port = port;
  }

  /**
   * Sets the timeout time when accepting connections.
   * The default is half a second. This means that stopping the
   * server may take up to timeout duration to actually stop.
   * The server must be stopped and restarted for the timeout
   * change to be effective.
   *
   * @param timeout the timeout time in ms.
   */
  final public void setTimeout(int timeout)
  {
    this.timeout = timeout;
  }

  /**
   * Sets the maximum number of waiting connections accepted by the
   * operating system. The default is 20.
   * The server must be closed and restarted for the backlog
   * change to be in effect.
   *
   * @param backlog the maximum number of connections.
   */
  final public void setBacklog(int backlog)
  {
    this.backlog = backlog;
  }

// RUN METHOD -------------------------------------------------------

  /**
   * Runs the listening thread that allows clients to connect.
   * Not to be called.
   */
  final public void run()
  {
    // call the hook method to notify that the server is starting
    // 呼叫 Hook 函式去提醒 Server 已經開始
    serverStarted();

    try
    {
      // Repeatedly waits for a new client connection, accepts it, and
      // starts a new thread to handle data exchange.
      // 反覆等待新 Client 的連接，接受它，並啟動一個新的執行緒來處理資料
      // 交換
      while(!readyToStop)
      {
        try
        {
          // Wait here for new connection attempts, or a timeout
          Socket clientSocket = serverSocket.accept();

          // When a client is accepted, create a thread to handle
          // the data exchange, then add it to thread group

          synchronized(this)
          {
            ConnectionToClient c = new ConnectionToClient(
              this.clientThreadGroup, clientSocket, this);
          }
        }
        catch (InterruptedIOException exception)
        {
          // This will be thrown when a timeout occurs.
          // The server will continue to listen if not ready to stop.
          // 當超時時這裡將會拋出例外。如果尚未準備結束，Server 會繼續聆聽
        }
      }

      // call the hook method to notify that the server has stopped
      serverStopped();
    }
    catch (IOException exception)
    {
      if (!readyToStop)
      {
        // Closing the socket must have thrown a SocketException
        // 關閉 socket 時必須拋出 SocketException 例外
        listeningException(exception);
      }
      else
      {
        serverStopped();
      }
    }
    finally
    {
      readyToStop = true;
      connectionListener = null;
    }
  }


// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

  /**
   * Hook method called each time a new client connection is
   * accepted. The default implementation does nothing.
   * 當有新的 Client 連接時會呼叫此 Hook 函式，預設不做任何操作。
   * @param client the connection connected to the client.
   */
  protected void clientConnected(ConnectionToClient client) {}

  /**
   * Hook method called each time a client disconnects.
   * The default implementation does nothing. The method
   * may be overridden by subclasses but should remains synchronized.
   * 每次 Client 斷開連結時會呼叫的 Hook。預設不做任何操作。此函式可以
   * 被子類別覆寫，但是應該保持同步。
   *
   * @param client the connection with the client.
   */
  synchronized protected void clientDisconnected(
    ConnectionToClient client) {}

  /**
   * Hook method called each time an exception is thrown in a
   * ConnectionToClient thread.
   * The method may be overridden by subclasses but should remains
   * synchronized.
   * 每次在 ConnectionToClient 執行緒中引發例外時會呼叫的 Hook
  //  * 此方法可以被子類別覆寫，但應該保持同步。
   *
   * @param client the client that raised the exception.
   * @param Throwable the exception thrown.
   */
  synchronized protected void clientException(
    ConnectionToClient client, Throwable exception) {}

  /**
   * Hook method called when the server stops accepting
   * connections because an exception has been raised.
   * The default implementation does nothing.
   * This method may be overridden by subclasses.
   * 當 Server 由於例外發生而停止接受連接時呼叫的 Hook 
   * 函式。預設不進行任何操作。子類別可能會覆寫此函式。
   *
   * @param exception the exception raised.
   */
  protected void listeningException(Throwable exception) {}

  /**
   * Hook method called when the server starts listening for
   * connections.  The default implementation does nothing.
   * The method may be overridden by subclasses.
   * Server 開始聆聽時會呼叫的 Hook 函式。預設不進行任何操作。
   * 可以被子類別覆寫
   */
  protected void serverStarted() {}

  /**
   * Hook method called when the server stops accepting
   * connections.  The default implementation
   * does nothing. This method may be overridden by subclasses.
   * 當 Server 停止接受連接時會呼叫的 Hook。預設不進行任何操作。
   * 可以被子類別覆寫
   */
  protected void serverStopped() {}

  /**
   * Hook method called when the server is closed.
   * The default implementation does nothing. This method may be
   * overridden by subclasses. When the server is closed while still
   * listening, serverStopped() will also be called.
   * 關閉 Server 時會呼叫的 Hook 函式。預設不進行任何操作。
   * 可以被子類別覆寫。當 Server 還在聆聽時關閉 Server 將呼叫 
   * serverStopped
   */
  protected void serverClosed() {}

  /**
   * Handles a command sent from one client to the server.
   * This MUST be implemented by subclasses, who should respond to
   * messages.
   * This method is called by a synchronized method so it is also
   * implicitly synchronized.
   * 處理從 Client 發送到 Server 的命令。必須由子類別實作。此函式由同步
   * 的函式呼叫，因此它也是隱性同步
   *
   * @param msg   the message sent.
   * @param client the connection connected to the client that
   *  sent the message.
   */
  protected abstract void handleMessageFromClient(
    Object msg, ConnectionToClient client);


// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

  /**
   * Receives a command sent from the client to the server.
   * Called by the run method of <code>ConnectionToClient</code>
   * instances that are watching for messages coming from the server
   * This method is synchronized to ensure that whatever effects it has
   * do not conflict with work being done by other threads. The method
   * simply calls the <code>handleMessageFromClient</code> slot method.
   * 接收從 Client 發送到 Server 的命令。由正在監視來自 Server 的 
   * ConnectionToClient 實例的 run 函式呼叫
   * 同步此方法以確保其產生的任何影響都不會與其他執行緒所做的工作衝突。該
   * 函式僅呼叫 handleMessageFromClient。
   *
   * @param msg   the message sent.
   * @param client the connection connected to the client that
   *  sent the message.
   */
  final synchronized void receiveMessageFromClient(
    Object msg, ConnectionToClient client)
  {
    this.handleMessageFromClient(msg, client);
  }
}
// End of AbstractServer Class
```

+ File `ocsf/server/ConnectionToClient.java`:

```java
// This file contains material supporting section 3.8 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package ocsf.server;

import java.io.*;
import java.net.*;
import java.util.*;

/**
* An instance of this class is created by the server when a client
* connects. It accepts messages coming from the client and is
* responsible for sending data to the client since the socket is
* private to this class. The AbstractServer contains a set of
* instances of this class and is responsible for adding and deleting
* them.<p>
* Client 連接時，Server 將創建此類的實例。它接受來自 Client 的訊息，並
* 負責將資料發送給 Client，因為 socket 是此類的私有成員。AbstractServer
* 會包含此類的一組實例，並負責增加及刪除它們。
*
* Project Name: OCSF (Object Client-Server Framework)<p>
*
* @author Dr Robert Lagani&egrave;re
* @author Dr Timothy C. Lethbridge
* @author Fran&ccedil;ois B&eacute;langer
* @author Paul Holden
* @version February 2001 (2.12)
*/
public class ConnectionToClient extends Thread
{
// INSTANCE VARIABLES ***********************************************

  /**
  * A reference to the Server that created this instance.
  * 用來指向產生此實例的 Server 的參考
  */
  private AbstractServer server;

  /**
  * Sockets are used in the operating system as channels
  * of communication between two processes.
  * Socket 是作業系統中兩個程序用來溝通的管道
  * @see java.net.Socket
  */
  private Socket clientSocket;

  /**
  * Stream used to read from the client.
  * 從 Client 讀取的資料流
  */
  private ObjectInputStream input;

  /**
  * Stream used to write to the client.
  * 寫入到 Client 的資料流
  */
  private ObjectOutputStream output;

  /**
  * Indicates if the thread is ready to stop. Set to true when closing
  * of the connection is initiated.
  * 指示執行緒是否已經準備好停止。啟動關閉連結時設置為 true
  */
  private boolean readyToStop;

  /**
   * Map to save information about the client such as its login ID.
   * The initial size of the map is small since it is not expected
   * that concrete servers will want to store many different types of
   * information about each client. Used by the setInfo and getInfo
   * methods.
   * 一個保存有關 client 資訊的資料結構，例如登入 ID。此資料結構的初始大小
   * 很小，因為 Server 預計不會儲存每個 Client 許多不同類型的訊息。由
   * setInfo 和 getInfo 使用
   */
  private HashMap savedInfo = new HashMap(10);


// CONSTRUCTORS *****************************************************

  /**
   * Constructs a new connection to a client.
   * 創建一個與 client 的連結
   *
   * @param group the thread group that contains the connections.
   * @param clientSocket contains the client's socket.
   * @param server a reference to the server that created
   *        this instance
   * @exception IOException if an I/O error occur when creating
   *        the connection.
   */
  ConnectionToClient(ThreadGroup group, Socket clientSocket,
    AbstractServer server) throws IOException
  {
    super(group,(Runnable)null);
    // Initialize variables
    this.clientSocket = clientSocket;
    this.server = server;

    //Initialize the objects streams
    try
    {
      input = new ObjectInputStream(clientSocket.getInputStream());
      output = new ObjectOutputStream(clientSocket.getOutputStream());
    }
    catch (IOException ex)
    {
      try
      {
        closeAll();
      }
      catch (Exception exc) { }

      throw ex;  // Rethrow the exception.
    }

    readyToStop = false;
    start(); // Start the thread waits for data from the socket
  }

// INSTANCE METHODS *************************************************

  /**
   * Sends an object to the client.
   * 傳送一個物件給 client
   *
   * @param msg the message to be sent.
   * @exception IOException if an I/O error occur when sending the 
   *    message.
   */
  final public void sendToClient(Object msg) throws IOException
  {
    if (clientSocket == null || output == null)
      throw new SocketException("socket does not exist");

    output.writeObject(msg);
  }

  /**
   * Closes the client.
   * 關閉此 client
   * If the connection is already closed, this
   * call has no effect.
   *
   * @exception IOException if an error occurs when closing the socket.
   */
  final public void close() throws IOException
  {
    readyToStop = true; // Set the flag that tells the thread to stop

    try
    {
      closeAll();
    }
    finally
    {
      server.clientDisconnected(this);
    }
  }

// ACCESSING METHODS ------------------------------------------------

  /**
   * Returns the address of the client.
   *
   * @return the client's Internet address.
   */
  final public InetAddress getInetAddress()
  {
    return clientSocket == null ? null : clientSocket.getInetAddress();
  }

  /**
   * Returns a string representation of the client.
   *
   * @return the client's description.
   */
  public String toString()
  {
    return clientSocket == null ? null :
      clientSocket.getInetAddress().getHostName()
        +" (" + clientSocket.getInetAddress().getHostAddress() + ")";
  }

  /**
   * Saves arbitrary information about this client. Designed to be
   * used by concrete subclasses of AbstractServer. Based on a hash map.
   * 保存有關此 Client 的任意資訊。設計供 AbstractServer 的具體子類別使用
   *
   * @param infoType   identifies the type of information
   * @param info       the information itself.
   */
  public void setInfo(String infoType, Object info)
  {
    savedInfo.put(infoType, info);
  }

  /**
   * Returns information about the client saved using setInfo.
   * Based on a hash map.
   * 用於回傳已經儲存的 client 資訊
   *
   * @param infoType   identifies the type of information
   */
  public Object getInfo(String infoType)
  {
    return savedInfo.get(infoType);
  }

// RUN METHOD -------------------------------------------------------

  /**
   * Constantly reads the client's input stream.
   * Sends all objects that are read to the server.
   * Not to be called.
   * 不斷讀取 client 的輸入流，將所有讀取得物件發送到 Server
   */
  final public void run()
  {
    server.clientConnected(this);

    // This loop reads the input stream and responds to messages
    // from clients
    try
    {
      // The message from the client
      Object msg;

      while (!readyToStop)
      {
        // This block waits until it reads a message from the client
        // and then sends it for handling by the server
        // 此區塊將一直等待直到讀取到來自 client 的訊息，然後將其傳給
        // server 來處理
        msg = input.readObject();
        server.receiveMessageFromClient(msg, this);
      }
    }
    catch (Exception exception)
    {
      if (!readyToStop)
      {
        try
        {
          closeAll();
        }
        catch (Exception ex) { }

        server.clientException(this, exception);
      }
    }
  }


// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

  /**
   * Closes all connection to the server.
   *
   * @exception IOException if an I/O error occur when closing the 
   *     connection.
   */
  private void closeAll() throws IOException
  {
    try
    {
      // Close the socket
      if (clientSocket != null)
        clientSocket.close();

      // Close the output stream
      if (output != null)
        output.close();

      // Close the input stream
      if (input != null)
        input.close();
    }
    finally
    {
      // Set the streams and the sockets to NULL no matter what
      // Doing so allows, but does not require, any finalizers
      // of these objects to reclaim system resources if and
      // when they are garbage collected.
      output = null;
      input = null;
      clientSocket = null;
    }
  }

  /**
   * This method is called by garbage collection.
   */
  protected void finalize()
  {
    try
    {
      closeAll();
    }
    catch(IOException e) {}
  }
}
// End of ConnectionToClient class
```

