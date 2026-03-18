#pragma once
#include "PowerUp.h"

class PlayerState {
public:
    static PlayerState& GetInstance() {
        static PlayerState instance;
        return instance;
    }

    PowerupType activePowerup = PowerupType::None;
    

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
    }

private:
    PlayerState() = default;
};