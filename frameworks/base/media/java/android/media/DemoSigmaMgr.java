package android.media;

import android.os.IBinder;
import android.media.ISigmaService;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import android.content.Context;
import android.annotation.Nullable;
import android.annotation.SystemApi;

public class DemoSigmaMgr {
   public DemoSigmaMgr() {
   }

   ISigmaService sigmaservice = null;
   private ISigmaService getService() {
	   if (sigmaservice != null) {
		  return sigmaservice;
   }
   try {
   IBinder binder = ServiceManager.getService(Context.SIGMA_SERVICE);
   sigmaservice = ISigmaService.Stub.asInterface(binder);
   } catch (Exception e) {
	android.util.Log.d("Error", "exception " + e);
   }
   return sigmaservice;
   }
  
  
  @Nullable
  public String getName() {
    try {
        return getService().getName();
    } catch (RemoteException e) {
        
        e.printStackTrace();
        return null; 
    }
}


  public int add(int x, int y) {
    try {
        return getService().add(x, y);
    } catch (RemoteException e) {
        
        e.printStackTrace();
        return 0; 
    }
  }
}
