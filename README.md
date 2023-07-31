<h1 align="center"> Creating a System Service </h1>

<p> This is an AOSP example which demonstrates added a new System Service to your AOSP build </p>
<p> This system service for now, returns null values. You can modify the code to make it return something else. </p>

- Phone- **Pixel 5a(5G)**
- Branch- **android-11.0.0_r48**
- Linux- **Ubuntu 18.04.6- LTS**

Only the modified files have been included in this repository. In
- SystemServiceRegistry.java
- Context.java
- Android.mk
<p>Search for 'Anish' to see what changes have been made. </p>

<p>Steps that have been followed-</p>
    <p>1. Create a new java class, SigmaManager.java and place it under- 
       frameworks/ base/ media/ java/ android/ media/ 
       Take a look at AudioManager.java for the structure of the code. The manager class should include a context member variable. So make sure to include that. </p>
    <p>2. Register SigmaManager in SystemServiceRegistry.java.
       The file is located under-
       frameworks/ base/ core/ java/ android/ app/ </p>
    <p>3. Add a new String identifier entry in Context.java located under-
       frameworks/ base/ core/ java/ android/ content/ Context.java </p>
    <p>4. Run the ‘m update-api’ command followed by ‘m -j20’. You should be able to compile without any errors. </p>
    <p>5. Write two functions, String read(int maxLength) and int write(String value) in IsigmaService.aidl. You will have to create this file and then place it under-
       frameworks/ base/ media/ java/ android/ media/ 
       Refer to IaudioService.aidl under the same file path for the code structure. </p>
    <p>6. Create a new Java class and name it SigmaService.java and save it under-
       frameworks/ base/ services/ core/ java/ com/ android/ server/ audio/
       Make sure to extend your ISigmaService.Stub and implement your
       AIDL interface functions! Also note the Lifecycle subclass that actually extends SystemService.
       That's your core for hooking into the system service lifecycle system. Note that you probably
       don't need anything inside onBootPhase() as our service is simpler than that. For now, you can have your two functions just return "null" and 0, or any other placeholder
       value. </p>
    <p>7. Go to frameworks/base/services/java/com/android/server/SystemServer.java and
       find the place where AudioService is started. In the same manner, start your SigmaService here. </p>
    <p>8. Go back to your SigmaManager.java. Now, define your public interface functions: read()
       and write(), mirroring your AIDL interface. Then, acquire a handle to your ISigmaService AIDL
       service. Look at AudioManager.java for an example on how to do this. Note the try/catch block catching a RemoteException! This is where you make the IPC call over Binder. This is where
       your app process invokes a function living in the system_server process. </p>

**TIP- Once you make the changes and then run m update-api, you are most likely to encounter a few errors. The most helpful trick to debugging is, debug errors one by one and try to analyze the codes to check for what went wrong. Most of the times the errors exists because of failing to import something or failing to create a constructor.

  9.  You can test out all of these changes in android studio as well.
When you first flash and boot, you could be stuck in boot loop. It is because of an SELinux error.  SELinux defines permissions for system-level facilities, and we haven't told the Android system that our service has permission to spin up.  To fix this,
    • go to device/google/crosshatch-sepolicy/private (or whichever build flavor you are
      running, e.g. barbet-sepolicy) and find two files: service.te and service_contexts.
    • If you are using a barbet device, these devices make use of the redbull sepolicy and the redbull kernel. The way you can verify this-
      cd device/google/barbet
	grep sepolicy -r .
	grep include -r.
	grep ^include -r.
	After the last command, we are able to see that device-barbet.mk includes 	device/google/redbull/device-common.mk
    • Inside service.te, define a new SELinux policy service type like so:
      type sigma_service, app_api_service, system_server_service, service_manager_type;
      and inside service_contexts, define the instance of your service like so:
      sigma  			u:object_r:sigma_service:s0
    • Rebuild and you should be able to boot.


