package com.pierce.multipthread;

import java.util.UUID;

public class UUIDUtils {
    public static String get() {
        return UUID.randomUUID().toString();
    }
}
