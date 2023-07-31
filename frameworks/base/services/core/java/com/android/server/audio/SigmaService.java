package com.android.server;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbManager;
import android.hidl.manager.V1_0.IServiceManager;
import android.os.Binder;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;

import android.os.SystemProperties;
import android.util.Slog;
import android.util.Log;
import com.android.server.EventLogTags;
import android.media.ISigmaService;
import com.android.server.SystemService;


public class SigmaService extends ISigmaService.Stub {
   static final String TAG = "SigmaService";
   private Context mContext;
   private int mNativePointer;

   public static final class Lifecycle extends SystemService {
        private SigmaService mService;

        public Lifecycle(Context context) {
            super(context);
            mService = new SigmaService(context);
        }   
        @Override
        public void onStart() {
            publishBinderService(Context.AUDIO_SERVICE, mService);
        }

        @Override
        public void onBootPhase(int phase) {
        }
    }


   public SigmaService(Context context) {
      super();
      mContext = context;
      Log.i(TAG, "Sigma Service started");
      mNativePointer = init_native();
   }

   public String getName() {
      return "Anish Puranik at Sigma Connectivity Inc";
   }

   public int add(int a,int b){
      return a+b;
   }

   // Native functions by Anish
   public String retString(int numtoPrint) {
      int num;

      byte[] buffer = new byte[numtoPrint];
      num = retStringNative(mNativePointer, buffer);
      return new String(buffer, 0, num);
   }

   public int give(String mString) {
      byte[] buffer = mString.getBytes();
      return write_native(mNativePointer, buffer);
   }

   private static native int retStringNative(int ptr, byte[] buffer);
   private static native int write_native(int ptr, byte[] buffer);
   private static native int init_native();
}

