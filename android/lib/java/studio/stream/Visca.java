package studio.stream;

public class Visca{
    private long pointer;
    
    private native void nativeInit();
    private native void nativePanTilt();
    private native void nativeZoom();
    private native void nativePresetSet();
    private native void nativePresetCall();
    private native void nativeRelease();
    private native static void nativeClassInit();

    static {
        System.loadLibrary("visca");
        nativeClassInit();
    }

    public Visca(){
        nativeInit();
    }

    public void zoom(int speed){
        nativeZoom();
    }

    public void panTilt(int panSpeed, int tiltSpeed){
        nativePanTilt();
    }

    public void presetSet(int preset){
        nativePresetSet();
    }


    public void presetCall(int preset){
        nativePresetCall();
    }

    protected void finalize() throws Throwable {
        nativeRelease();
    }

}