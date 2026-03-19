#pragma once
#include "PowerUp.h"

class PlayerState {
public:
    static PlayerState& GetInstance() {
        static PlayerState instance;
        return instance;
    }

    PowerupType activePowerup = PowerupType::None;
    
    //HP 
    int maxHp = 2;
    int currentHp = 2;


    void TakeDamage() {
        if (isInvincible) return;
        currentHp--;
    }

    bool IsDead() const { return currentHp <= 0; }

    void AddHp(int amount = 1) {
        maxHp += amount;       
        currentHp += amount;    
    }


    // Invincibilité
    bool isInvincible = false;
    float invincibilityTimer = 0.f;
    float invincibilityDuration = 3.f;


    void ActivateInvincibility() {
        isInvincible = true;
        invincibilityTimer = invincibilityDuration;
    }

    void UpdateInvincibility(float deltaTime) {
        if (isInvincible) {
            invincibilityTimer -= deltaTime;
            if (invincibilityTimer <= 0.f) {
                isInvincible = false;
                invincibilityTimer = 0.f;
            }
        }
    }

    void Reset() {
        activePowerup = PowerupType::None;
        isInvincible = false;
        invincibilityTimer = 0.f;
        currentHp = maxHp; // reset HP au max
    }

    void SoftReset() {
        // Reset après mort — garde les HP et maxHp
        isInvincible = false;
        invincibilityTimer = 0.f;
    }

private:
    PlayerState() = default;
};