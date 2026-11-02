#include "crypto_manager.h"

CryptoManager &CryptoManager::instance(){
    static CryptoManager manager;
    return manager;
}
