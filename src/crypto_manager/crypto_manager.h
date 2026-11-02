#ifndef CRYPTO_MANAGER_H
#define CRYPTO_MANAGER_H

class CryptoManager
{

public:
    static CryptoManager &instance();

    CryptoManager(const CryptoManager &) = delete;
    CryptoManager &operator=(const CryptoManager &) = delete;

private:
    CryptoManager() = default;

};

#endif
