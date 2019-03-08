package com.pierce.multipthread;

public class PThread {

    static {
        System.loadLibrary("mpthread");
    }

    public native void init();
    public native void pthread();
    public native void destroy();

}
