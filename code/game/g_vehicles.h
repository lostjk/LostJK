/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#ifndef __G_VEHICLES_H
#define __G_VEHICLES_H

#include "../qcommon/q_shared.h"
#include "g_public.h"

typedef enum
{
	VH_NONE = 0,
	VH_WALKER,		//something you ride inside of, it walks like you, like an AT-ST
	VH_FIGHTER,		//something you fly inside of, like an X-Wing or TIE fighter
	VH_SPEEDER,		//something you ride on that hovers, like a speeder or swoop
	VH_ANIMAL,		//animal you ride on top of that walks, like a tauntaun
	VH_FLIER,		//animal you ride on top of that flies, like a giant mynoc?
	VH_NUM_VEHICLES
} vehicleType_t;

enum	EWeaponPose
{
	WPOSE_NONE	= 0,
	WPOSE_BLASTER,
	WPOSE_SABERLEFT,
	WPOSE_SABERRIGHT,
};

extern stringID_table_t VehicleTable[VH_NUM_VEHICLES+1];

#define NO_PILOT_DIE_TIME 10000

//===========================================================================================================
//START VEHICLE WEAPONS
//===========================================================================================================
typedef struct
{
//*** IMPORTANT!!! *** vWeapFields table correponds to this structure!
	char	*name;
	qboolean	bIsProjectile;	//traceline or entity?
	qboolean	bHasGravity;	//if a projectile, drops
	qboolean	bIonWeapon;//disables ship shields and sends them out of control
	qboolean	bSaberBlockable;//lightsabers can deflect this projectile
	int		iMuzzleFX;	//index of Muzzle Effect
	int		iModel;		//handle to the model used by this projectile
	int		iShotFX;	//index of Shot Effect
	int		iImpactFX;	//index of Impact Effect
	int		iG2MarkShaderHandle;	//index of shader to use for G2 marks made on other models when hit by this projectile
	float	fG2MarkSize;//size (diameter) of the ghoul2 mark
	int		iLoopSound;	//index of loopSound
	float	fSpeed;		//speed of projectile/range of traceline
	float	fHoming;		//0.0 = not homing, 0.5 = half vel to targ, half cur vel, 1.0 = all vel to targ
	float	fHomingFOV;
	int		iLockOnTime;	//0 = no lock time needed, else # of ms needed to lock on
	int		iDamage;		//damage done when traceline or projectile directly hits target
	int		iSplashDamage;//damage done to ents in splashRadius of end of traceline or projectile origin on impact
	float	fSplashRadius;//radius that ent must be in to take splashDamage (linear fall-off)
	int		iAmmoPerShot;	//how much "ammo" each shot takes
	int		iHealth;		//if non-zero, projectile can be shot, takes this much damage before being destroyed
	float	fWidth;		//width of traceline or bounding box of projecile (non-rotating!)
	float	fHeight;		//height of traceline or bounding box of projecile (non-rotating!)
	int		iLifeTime;	//removes itself after this amount of time
	qboolean	bExplodeOnExpire;	//when iLifeTime is up, explodes rather than simply removing itself
} vehWeaponInfo_t;

#define	VWFOFS(x) offsetof(vehWeaponInfo_t, x)

#define MAX_VEH_WEAPONS	16	//sigh... no more than 16 different vehicle weapons
#define VEH_WEAPON_BASE	0
#define VEH_WEAPON_NONE	-1

extern vehWeaponInfo_t g_vehWeaponInfo[MAX_VEH_WEAPONS];
extern int	numVehicleWeapons;

//===========================================================================================================
//END VEHICLE WEAPONS
//===========================================================================================================

// The maximum number of muzzles a vehicle may have.
#define		MAX_VEHICLE_MUZZLES			10

// The maximum number of exhausts a vehicle may have.
#define		MAX_VEHICLE_EXHAUSTS		4

// The maxiumum number of different weapons a vehicle may have
#define		MAX_VEHICLE_WEAPONS			2
#define		MAX_VEHICLE_TURRETS			2
#define		MAX_VEHICLE_TURRET_MUZZLES	2

typedef struct
{
	int			iWeapon;	//what vehWeaponInfo index to use
	int			iDelay;		//delay between turret muzzle shots
	int			iAmmoMax;	//how much ammo it has
	int			iAmmoRechargeMS;	//how many MS between every point of recharged ammo
	char		*yawBone;	//bone on ship that this turret uses to yaw
	char		*pitchBone;	//bone on ship that this turret uses to pitch
	int			yawAxis;	//axis on yawBone to which we should to apply the yaw angles
	int			pitchAxis;	//axis on pitchBone to which we should to apply the pitch angles
	float		yawClampLeft;	//how far the turret is allowed to turn left
	float		yawClampRight;	//how far the turret is allowed to turn right
	float		pitchClampUp;	//how far the turret is allowed to title up
	float		pitchClampDown; //how far the turret is allowed to tilt down
	int			iMuzzle[MAX_VEHICLE_TURRET_MUZZLES];//iMuzzle-1 = index of ship's muzzle to fire this turret's 1st and 2nd shots from
	char		*gunnerViewTag;//Where to put the view origin of the gunner (name)
	float		fTurnSpeed;	//how quickly the turret can turn
	qboolean	bAI;	//whether or not the turret auto-targets enemies when it's not manned
	qboolean	bAILead;//whether
	float		fAIRange;	//how far away the AI will look for enemies
	int			passengerNum;//which passenger, if any, has control of this turret (overrides AI)
} turretStats_t;

typedef struct
{
//*** IMPORTANT!!! *** See note at top of next structure!!! ***
	// Weapon stuff.
	int			ID;//index into the weapon data
	// The delay between shots for each weapon.
	int			delay;
	// Whether or not all the muzzles for each weapon can be linked together (linked delay = weapon delay * number of muzzles linked!)
	int			linkable;
	// Whether or not to auto-aim the projectiles/tracelines at the thing under the crosshair when we fire
	qboolean	aimCorrect;
	//maximum ammo
	int			ammoMax;
	//ammo recharge rate - milliseconds per unit (minimum of 100, which is 10 ammo per second)
	int			ammoRechargeMS;
	//sound to play when out of ammo (plays default "no ammo" sound if none specified)
	int			soundNoAmmo;
} vehWeaponStats_t;

// Compiler pre-define.
struct Vehicle_t;

typedef struct
{
//*** IMPORTANT!!! *** vehFields table correponds to this structure!
	char		*name;	//unique name of the vehicle

	//general data
	vehicleType_t	type;	//what kind of vehicle
	int			numHands;	//if 2 hands, no weapons, if 1 hand, can use 1-handed weapons, if 0 hands, can use 2-handed weapons
	float		lookPitch;	//How far you can look up and down off the forward of the vehicle
	float		lookYaw;	//How far you can look left and right off the forward of the vehicle
	float		length;		//how long it is - used for body length traces when turning/moving?
	float		width;		//how wide it is - used for body length traces when turning/moving?
	float		height;		//how tall it is - used for body length traces when turning/moving?
	vec3_t		centerOfGravity;//offset from origin: {forward, right, up} as a modifier on that dimension (-1.0f is all the way back, 1.0f is all the way forward)

	//speed stats
	float		speedMax;		//top speed
	float		turboSpeed;		//turbo speed
	float		speedMin;		//if < 0, can go in reverse
	float		speedIdle;		//what speed it drifts to when no accel/decel input is given
	float		accelIdle;		//if speedIdle > 0, how quickly it goes up to that speed
	float		acceleration;	//when pressing on accelerator
	float		decelIdle;		//when giving no input, how quickly it drops to speedIdle
	float		throttleSticks;	//if true, speed stays at whatever you accel/decel to, unless you turbo or brake
	float		strafePerc;		//multiplier on current speed for strafing.  If 1.0f, you can strafe at the same speed as you're going forward, 0.5 is half, 0 is no strafing

	//handling stats
	float		bankingSpeed;	//how quickly it pitches and rolls (not under player control)
	float		rollLimit;		//how far it can roll to either side
	float		pitchLimit;		//how far it can roll forward or backward
	float		braking;		//when pressing on decelerator
	float		mouseYaw;		// The mouse yaw override.
	float		mousePitch;		// The mouse pitch override.
	float		turningSpeed;	//how quickly you can turn
	qboolean	turnWhenStopped;//whether or not you can turn when not moving
	float		traction;		//how much your command input affects velocity
	float		friction;		//how much velocity is cut on its own
	float		maxSlope;		//the max slope that it can go up with control
	qboolean	speedDependantTurning;//vehicle turns faster the faster it's going

	//durability stats
	int			mass;			//for momentum and impact force (player mass is 10)
	int			armor;			//total points of damage it can take
	int			shields;		//energy shield damage points
	int			shieldRechargeMS;//energy shield milliseconds per point recharged
	float		toughness;		//modifies incoming damage, 1.0 is normal, 0.5 is half, etc.  Simulates being made of tougher materials/construction
	int			malfunctionArmorLevel;//when armor drops to or below this point, start malfunctioning
	int			surfDestruction; //can parts of this thing be torn off on impact? -rww

	//individual "area" health -rww
	int			health_front;
	int			health_back;
	int			health_right;
	int			health_left;

	//visuals & sounds
	char		*model;			//what model to use - if make it an NPC's primary model, don't need this?
	char		*skin;			//what skin to use - if make it an NPC's primary model, don't need this?
	int			g2radius;		//render radius for the ghoul2 model
	int			riderAnim;		//what animation the rider uses
	int			radarIconHandle;//what icon to show on radar in MP
	char		*droidNPC;		//NPC to attach to *droidunit tag (if it exists in the model)

	int			soundOn;		//sound to play when get on it
	int			soundOff;		//sound to play when get off
	int			soundLoop;		//sound to loop while riding it
	int			soundTakeOff;	//sound to play when ship takes off
	int			soundEngineStart;//sound to play when ship's thrusters first activate
	int			soundSpin;		//sound to loop while spiraling out of control
	int			soundTurbo;		//sound to play when turbo/afterburner kicks in
	int			soundHyper;		//sound to play when ship lands
	int			soundLand;		//sound to play when ship lands
	int			soundFlyBy;		//sound to play when they buzz you
	int			soundFlyBy2;	//alternate sound to play when they buzz you
	int			soundShift1;	//sound to play when accelerating
	int			soundShift2;	//sound to play when accelerating
	int			soundShift3;	//sound to play when decelerating
	int			soundShift4;	//sound to play when decelerating

	int			iExhaustFX;		//exhaust effect, played from "*exhaust" bolt(s)
	int			iTurboFX;		//turbo exhaust effect, played from "*exhaust" bolt(s) when ship is in "turbo" mode
	int			iTurboStartFX;	//turbo begin effect, played from "*exhaust" bolts when "turbo" mode begins
	int			iTrailFX;		//trail effect, played from "*trail" bolt(s)
	int			iImpactFX;		//impact effect, for when it bumps into something
	int			iExplodeFX;		//explosion effect, for when it blows up (should have the sound built into explosion effect)
	int			iWakeFX;		//effect it makes when going across water
	int			iDmgFX;			//effect to play on damage from a weapon or something
	int			iArmorLowFX;	//played when armor is less than 30% of full
	int			iArmorGoneFX;	//played when on armor is completely gone

	//Weapon stats
	vehWeaponStats_t	weapon[MAX_VEHICLE_WEAPONS];

	// Which weapon a muzzle fires (has to match one of the weapons this vehicle has). So 1 would be weapon 1,
	// 2 would be weapon 2 and so on.
	int			weapMuzzle[MAX_VEHICLE_MUZZLES];

	//turrets (if any) on the vehicle
	turretStats_t	turret[MAX_VEHICLE_TURRETS];

	// The max height before this ship (?) starts (auto)landing.
	float landingHeight;

	//other misc stats
	int			gravity;		//normal is 800
	float		hoverHeight;	//if 0, it's a ground vehicle
	float		hoverStrength;	//how hard it pushes off ground when less than hover height... causes "bounce", like shocks
	qboolean	waterProof;		//can drive underwater if it has to
	float		bouyancy;		//when in water, how high it floats (1 is neutral bouyancy)
	int			fuelMax;		//how much fuel it can hold (capacity)
	int			fuelRate;		//how quickly is uses up fuel
	int			turboDuration;	//how long turbo lasts
	int			turboRecharge;	//how long turbo takes to recharge
	int			visibility;		//for sight alerts
	int			loudness;		//for sound alerts
	float		explosionRadius;//range of explosion
	int			explosionDamage;//damage of explosion

	int			maxPassengers;	// The max number of passengers this vehicle may have (Default = 0).
	qboolean	hideRider;		// rider (and passengers?) should not be drawn
	qboolean	killRiderOnDeath;//if rider is on vehicle when it dies, they should die
	qboolean	flammable;		//whether or not the vehicle should catch on fire before it explodes
	int			explosionDelay;	//how long the vehicle should be on fire/dying before it explodes
	//camera stuff
	qboolean	cameraOverride;	//whether or not to use all of the following 3rd person camera override values
	float		cameraRange;	//how far back the camera should be - normal is 80
	float		cameraVertOffset;//how high over the vehicle origin the camera should be - normal is 16
	float		cameraHorzOffset;//how far to left/right (negative/positive) of of the vehicle origin the camera should be - normal is 0
	float		cameraPitchOffset;//a modifier on the camera's pitch (up/down angle) to the vehicle - normal is 0
	float		cameraFOV;		//third person camera FOV, default is 80
	float		cameraAlpha;	//fade out the vehicle to this alpha (0.1-1.0f) if it's in the way of the crosshair
	qboolean	cameraPitchDependantVertOffset;//use the hacky AT-ST pitch dependant vertical offset

	//NOTE: some info on what vehicle weapon to use?  Like ATST or TIE bomber or TIE fighter or X-Wing...?

//===VEH_PARM_MAX========================================================================
//*** IMPORTANT!!! *** vehFields table correponds to this structure!

//THE FOLLOWING FIELDS are not in the vehFields table because they are internal variables, not read in from the .veh file
	int			modelIndex;		//set internally, not until this vehicle is spawned into the level

	// NOTE: Please note that most of this stuff has been converted from C++ classes to generic C.
	// This part of the structure is used to simulate inheritance for vehicles. The basic idea is that all vehicle use
	// this vehicle interface since they declare their own functions and assign the function pointer to the
	// corresponding function. Meanwhile, the base logic can still call the appropriate functions. In C++ talk all
	// of these functions (pointers) are pure virtuals and this is an abstract base class (although it cannot be
	// inherited from, only contained and reimplemented (through an object and a setup function respectively)). -AReis

	// Makes sure that the vehicle is properly animated.
	void (*AnimateVehicle)( Vehicle_t *pVeh );

	// Makes sure that the rider's in this vehicle are properly animated.
	void (*AnimateRiders)( Vehicle_t *pVeh );

	// Determine whether this entity is able to board this vehicle or not.
	bool (*ValidateBoard)( Vehicle_t *pVeh, gentity_t *pEnt );

	// Set the parent entity of this Vehicle NPC.
	void (*SetParent)( Vehicle_t *pVeh, gentity_t *pParentEntity );

	// Add a pilot to the vehicle.
	void (*SetPilot)( Vehicle_t *pVeh, gentity_t *pPilot );

	// Add a passenger to the vehicle (false if we're full).
	bool (*AddPassenger)( Vehicle_t *pVeh );

	// Animate the vehicle and it's riders.
	void (*Animate)( Vehicle_t *pVeh );

	// Board this Vehicle (get on). The first entity to board an empty vehicle becomes the Pilot.
	bool (*Board)( Vehicle_t *pVeh, gentity_t *pEnt );

	// Eject an entity from the vehicle.
	bool (*Eject)( Vehicle_t *pVeh, gentity_t *pEnt, qboolean forceEject );

	// Eject all the inhabitants of this vehicle.
	bool (*EjectAll)( Vehicle_t *pVeh );

	// Start a delay until the vehicle dies.
	void (*StartDeathDelay)( Vehicle_t *pVeh, int iDelayTime );

	// Update death sequence.
	void (*DeathUpdate)( Vehicle_t *pVeh );

	// Register all the assets used by this vehicle.
	void (*RegisterAssets)( Vehicle_t *pVeh );

	// Initialize the vehicle (should be called by Spawn?).
	bool (*Initialize)( Vehicle_t *pVeh );

	// Like a think or move command, this updates various vehicle properties.
	bool (*Update)( Vehicle_t *pVeh, const usercmd_t *pUcmd );

	// Update the properties of a Rider (that may reflect what happens to the vehicle).
	//
	//	[return]		bool			True if still in vehicle, false if otherwise.
	bool (*UpdateRider)( Vehicle_t *pVeh, gentity_t *pRider, usercmd_t *pUcmd );

	// ProcessMoveCommands the Vehicle.
	void (*ProcessMoveCommands)( Vehicle_t *pVeh );

	// ProcessOrientCommands the Vehicle.
	void (*ProcessOrientCommands)( Vehicle_t *pVeh );

	// Attachs all the riders of this vehicle to their appropriate position/tag (*driver, *pass1, *pass2, whatever...).
	void (*AttachRiders)( Vehicle_t *pVeh );

	// Make someone invisible and un-collidable.
	void (*Ghost)( Vehicle_t *pVeh, gentity_t *pEnt );

	// Make someone visible and collidable.
	void (*UnGhost)( Vehicle_t *pVeh, gentity_t *pEnt );

	// Get the pilot of this vehicle.
	const gentity_t *(*GetPilot)( Vehicle_t *pVeh );

	// Whether this vehicle is currently inhabited (by anyone) or not.
	bool (*Inhabited)( Vehicle_t *pVeh );
} vehicleInfo_t;

#define	VFOFS(x) offsetof(vehicleInfo_t, x)

#define MAX_VEHICLES	16	//sigh... no more than 64 individual vehicles
extern vehicleInfo_t g_vehicleInfo[MAX_VEHICLES];
extern int	numVehicles;

// Load the function pointers for a vehicle into this shared vehicle info structure.
extern void G_SetSpeederVehicleFunctions( vehicleInfo_t *pVehInfo );
extern void G_SetAnimalVehicleFunctions( vehicleInfo_t *pVehInfo );
extern void G_SetFighterVehicleFunctions( vehicleInfo_t *pVehInfo );
extern void G_SetWalkerVehicleFunctions( vehicleInfo_t *pVehInfo );

// Setup the shared functions (one's that all vehicles would generally use).
extern void G_SetSharedVehicleFunctions( vehicleInfo_t *pVehInfo );

// Create/Allocate a new Animal Vehicle (initializing it as well).
extern void G_CreateSpeederNPC( Vehicle_t **pVeh, const char *strType );
extern void G_CreateAnimalNPC( Vehicle_t **pVeh, const char *strType );
extern void G_CreateFighterNPC( Vehicle_t **pVeh, const char *strType );
extern void G_CreateWalkerNPC( Vehicle_t **pVeh, const char *strType );

#define VEH_DEFAULT_SPEED_MAX		800.0f
#define VEH_DEFAULT_ACCEL			10.0f
#define VEH_DEFAULT_DECEL			10.0f
#define VEH_DEFAULT_STRAFE_PERC		0.5f
#define VEH_DEFAULT_BANKING_SPEED	0.5f
#define VEH_DEFAULT_ROLL_LIMIT		60.0f
#define VEH_DEFAULT_PITCH_LIMIT		90.0f
#define VEH_DEFAULT_BRAKING			10.0f
#define VEH_DEFAULT_TURNING_SPEED	1.0f
#define VEH_DEFAULT_TRACTION		8.0f
#define VEH_DEFAULT_FRICTION		1.0f
#define VEH_DEFAULT_MAX_SLOPE		0.85f
#define VEH_DEFAULT_MASS			200
#define VEH_DEFAULT_MAX_ARMOR		200
#define VEH_DEFAULT_TOUGHNESS		2.5f
#define VEH_DEFAULT_GRAVITY			800
#define VEH_DEFAULT_HOVER_HEIGHT	64.0f
#define VEH_DEFAULT_HOVER_STRENGTH	10.0f
#define VEH_DEFAULT_VISIBILITY		0
#define VEH_DEFAULT_LOUDNESS		0
#define VEH_DEFAULT_EXP_RAD			400.0f
#define VEH_DEFAULT_EXP_DMG			1000
#define VEH_MAX_PASSENGERS			10

#define VEH_MOUNT_THROW_LEFT		-5
#define	VEH_MOUNT_THROW_RIGHT		-6

#define MAX_STRAFE_TIME				2000.0f//FIXME: extern?
#define	MIN_LANDING_SPEED			200//equal to or less than this and close to ground = auto-slow-down to land
#define	MIN_LANDING_SLOPE			0.8f//must be pretty flat to land on the surf

#define VEHICLE_BASE				0
#define VEHICLE_NONE				-1

enum
{
	VEH_EJECT_LEFT,
	VEH_EJECT_RIGHT,
	VEH_EJECT_FRONT,
	VEH_EJECT_REAR,
	VEH_EJECT_TOP,
	VEH_EJECT_BOTTOM
};

// Vehicle flags.
enum
{
	VEH_NONE = 0, VEH_FLYING = 0x00000001, VEH_CRASHING = 0x00000002,
	VEH_LANDING = 0x00000004, VEH_BUCKING = 0x00000010, VEH_WINGSOPEN = 0x00000020,
	VEH_GEARSOPEN = 0x00000040, VEH_SLIDEBREAKING = 0x00000080, VEH_SPINNING = 0x00000100,
	VEH_OUTOFCONTROL = 0x00000200,
	VEH_SABERINLEFTHAND = 0x00000400,
	VEH_STRAFERAM = 0x00000800,
	VEH_ACCELERATORON = 0x00001000,
	VEH_ARMORLOW = 0x00002000,
	VEH_ARMORGONE = 0x00004000
};
//externed functions
extern void G_VehicleSpawn( gentity_t *self );

// A vehicle weapon muzzle.
#pragma pack(push, 4)
class SgMuzzle
{
public:
    SgVec3 m_vMuzzlePos;
    SgVec3 m_vMuzzleDir;
    int32_t m_iMuzzleWait;
    int8_t m_bFired;
}; // SgMuzzle
#pragma pack(pop)

struct Muzzle
{
    using SgType = SgMuzzle;


	// These are updated every frame and represent the current position and direction for the specific muzzle.
	vec3_t m_vMuzzlePos;
	vec3_t m_vMuzzleDir;

	// This is how long to wait before being able to fire a specific muzzle again. This is based on the firing rate
	// so that a firing rate of 10 rounds/sec would make this value initially 100 miliseconds.
	int m_iMuzzleWait;

	// whether this Muzzle was just fired or not (reset at muzzle flash code).
	bool m_bFired;


    void sg_export(
        SgType& dst) const
    {
        ::sg_export(m_vMuzzlePos, dst.m_vMuzzlePos);
        ::sg_export(m_vMuzzleDir, dst.m_vMuzzleDir);
        ::sg_export(m_iMuzzleWait, dst.m_iMuzzleWait);
        ::sg_export(m_bFired, dst.m_bFired);
    }

    void sg_import(
        const SgType& src)
    {
        ::sg_import(src.m_vMuzzlePos, m_vMuzzlePos);
        ::sg_import(src.m_vMuzzleDir, m_vMuzzleDir);
        ::sg_import(src.m_iMuzzleWait, m_iMuzzleWait);
        ::sg_import(src.m_bFired, m_bFired);
    }
};

//defines for impact damage surface stuff
#define	SHIPSURF_FRONT		1
#define	SHIPSURF_BACK		2
#define	SHIPSURF_RIGHT		3
#define	SHIPSURF_LEFT		4

#define	SHIPSURF_DAMAGE_FRONT_LIGHT		1
#define	SHIPSURF_DAMAGE_BACK_LIGHT		2
#define	SHIPSURF_DAMAGE_RIGHT_LIGHT		3
#define	SHIPSURF_DAMAGE_LEFT_LIGHT		4
#define	SHIPSURF_DAMAGE_FRONT_HEAVY		5
#define	SHIPSURF_DAMAGE_BACK_HEAVY		6
#define	SHIPSURF_DAMAGE_RIGHT_HEAVY		7
#define	SHIPSURF_DAMAGE_LEFT_HEAVY		8

//generic part bits
#define SHIPSURF_BROKEN_A	(1<<0) //gear 1
#define SHIPSURF_BROKEN_B	(1<<1) //gear 1
#define SHIPSURF_BROKEN_C	(1<<2) //wing 1
#define SHIPSURF_BROKEN_D	(1<<3) //wing 2
#define SHIPSURF_BROKEN_E	(1<<4) //wing 3
#define SHIPSURF_BROKEN_F	(1<<5) //wing 4

#pragma pack(push, 4)
class SgVehWeaponStatus
{
public:
    int32_t linked;
    int32_t ammo;
    int32_t lastAmmoInc;
    int32_t nextMuzzle;
}; // SgVehWeaponStatus
#pragma pack(pop)

typedef struct
{
    using SgType = SgVehWeaponStatus;


	//linked firing mode
	qboolean	linked;//weapon 1's muzzles are in linked firing mode
	//current weapon ammo
	int			ammo;
	//debouncer for ammo recharge
	int			lastAmmoInc;
	//which muzzle will fire next
	int			nextMuzzle;


    void sg_export(
        SgType& dst) const
    {
        ::sg_export(linked, dst.linked);
        ::sg_export(ammo, dst.ammo);
        ::sg_export(lastAmmoInc, dst.lastAmmoInc);
        ::sg_export(nextMuzzle, dst.nextMuzzle);
    }

    void sg_import(
        const SgType& src)
    {
        ::sg_import(src.linked, linked);
        ::sg_import(src.ammo, ammo);
        ::sg_import(src.lastAmmoInc, lastAmmoInc);
        ::sg_import(src.nextMuzzle, nextMuzzle);
    }
} vehWeaponStatus_t;

#pragma pack(push, 4)
class SgVehTurretStatus
{
public:
    int32_t ammo;
    int32_t lastAmmoInc;
    int32_t nextMuzzle;
    int32_t enemyEntNum;
    int32_t enemyHoldTime;
}; // SgVehTurretStatus
#pragma pack(pop)

typedef struct
{
    using SgType = SgVehTurretStatus;


	//current weapon ammo
	int			ammo;
	//debouncer for ammo recharge
	int			lastAmmoInc;
	//which muzzle will fire next
	int			nextMuzzle;
	//which entity they're after
	int			enemyEntNum;
	//how long to hold on to our current enemy
	int			enemyHoldTime;


    void sg_export(
        SgType& dst) const
    {
        ::sg_export(ammo, dst.ammo);
        ::sg_export(lastAmmoInc, dst.lastAmmoInc);
        ::sg_export(nextMuzzle, dst.nextMuzzle);
        ::sg_export(enemyEntNum, dst.enemyEntNum);
        ::sg_export(enemyHoldTime, dst.enemyHoldTime);
    }

    void sg_import(
        const SgType& src)
    {
        ::sg_import(src.ammo, ammo);
        ::sg_import(src.lastAmmoInc, lastAmmoInc);
        ::sg_import(src.nextMuzzle, nextMuzzle);
        ::sg_import(src.enemyEntNum, enemyEntNum);
        ::sg_import(src.enemyHoldTime, enemyHoldTime);
    }
} vehTurretStatus_t;

// This is the implementation of the vehicle interface and any of the other variables needed. This
// is what actually represents a vehicle. -AReis.
// !!!!!!!!!!!!!!!!!! loadsave affecting structure !!!!!!!!!!!!!!!!!!!!!!!
#pragma pack(push, 4)
class SgVehicle
{
public:
    int32_t m_pPilot;
    int32_t m_iPilotTime;
    int32_t m_bHasHadPilot;
    int32_t m_pDroidUnit;
    int32_t m_pParentEntity;
    int32_t m_iBoarding;
    int8_t m_bWasBoarding;
    SgVec3 m_vBoardingVelocity;
    float m_fTimeModifier;
    int32_t m_iLeftWingBone;
    int32_t m_iRightWingBone;
    SgArray<int32_t, MAX_VEHICLE_EXHAUSTS> m_iExhaustTag;
    SgArray<int32_t, MAX_VEHICLE_MUZZLES> m_iMuzzleTag;
    int32_t m_iDroidUnitTag;
    SgArray<int32_t, MAX_VEHICLE_TURRETS> m_iGunnerViewTag;
    SgArray<SgMuzzle, MAX_VEHICLE_MUZZLES> m_Muzzles;
    SgUserCmd m_ucmd;
    int32_t m_EjectDir;
    uint32_t m_ulFlags;
    SgVec3 m_vOrientation;
    int32_t m_fStrafeTime;
    SgVec3 m_vPrevOrientation;
    float m_vAngularVelocity;
    SgVec3 m_vFullAngleVelocity;
    int32_t m_iArmor;
    int32_t m_iShields;
    int32_t m_iLastFXTime;
    int32_t m_iDieTime;
    int32_t m_pVehicleInfo;
    SgTrace m_LandTrace;
    int32_t m_iRemovedSurfaces;
    int32_t m_iTurboTime;
    int32_t m_iDropTime;
    int32_t m_iSoundDebounceTimer;
    int32_t lastShieldInc;
    int32_t linkWeaponToggleHeld;
    SgArray<SgVehWeaponStatus, MAX_VEHICLE_WEAPONS> weaponStatus;
    SgArray<SgVehTurretStatus, MAX_VEHICLE_TURRETS> turretStatus;
    int32_t m_pOldPilot;
    int32_t m_safeJumpMountTime;
    float m_safeJumpMountRightDot;
}; // SgVehicle
#pragma pack(pop)

struct Vehicle_t
{
    using SgType = SgVehicle;


	// The entity who pilots/drives this vehicle.
	// NOTE: This is redundant (since m_pParentEntity->owner _should_ be the pilot). This makes things clearer though.
	gentity_t *m_pPilot;

	int m_iPilotTime; //if spawnflag to die without pilot and this < level.time then die.
	qboolean m_bHasHadPilot; //qtrue once the vehicle gets its first pilot

	//the droid unit NPC for this vehicle, if any
	gentity_t *m_pDroidUnit;

	// The entity from which this NPC comes from.
	gentity_t *m_pParentEntity;

	// If not zero, how long to wait before we can do anything with the vehicle (we're getting on still).
	// -1 = board from left, -2 = board from right, -3 = jump/quick board.  -4 & -5 = throw off existing pilot
	int		m_iBoarding;

	// Used to check if we've just started the boarding process
	bool	m_bWasBoarding;

	// The speed the vehicle maintains while boarding occurs (often zero)
	vec3_t	m_vBoardingVelocity;

	// Time modifier (must only be used in ProcessMoveCommands() and ProcessOrientCommands() and is updated in Update()).
	float m_fTimeModifier;

	// Ghoul2 Animation info.
	// NOTE: Since each vehicle has their own model instance, these bolts must be local to each vehicle as well.
	int m_iLeftWingBone;
	int m_iRightWingBone;
	//int m_iDriverTag;
	int m_iExhaustTag[MAX_VEHICLE_EXHAUSTS];
	int m_iMuzzleTag[MAX_VEHICLE_MUZZLES];
	int m_iDroidUnitTag;
	int	m_iGunnerViewTag[MAX_VEHICLE_TURRETS];//Where to put the view origin of the gunner (index)

	// This vehicles weapon muzzles.
	Muzzle m_Muzzles[MAX_VEHICLE_MUZZLES];

	// The user commands structure.
	usercmd_t m_ucmd;

	// The direction an entity will eject from the vehicle towards.
	int m_EjectDir;

	// Flags that describe the vehicles behavior.
	unsigned long m_ulFlags;

	// NOTE: Vehicle Type ID, Orientation, and Armor MUST be transmitted over the net.

	// Current angles of this vehicle.
	vec3_t		m_vOrientation;

	// How long you have strafed left or right (increments every frame that you strafe to right, decrements every frame you strafe left)
	int			m_fStrafeTime;

	// Previous angles of this vehicle.
	vec3_t		m_vPrevOrientation;

	// When control is lost on a speeder, current angular velocity is stored here and applied until landing
	float		m_vAngularVelocity;

	vec3_t		m_vFullAngleVelocity;

	// Current armor and shields of your vehicle (explodes if armor to 0).
	int			m_iArmor;	//hull strength - STAT_HEALTH on NPC
	int			m_iShields;	//energy shielding - STAT_ARMOR on NPC

	// Timer for all cgame-FX...? ex: exhaust?
	int			m_iLastFXTime;

	// When to die.
	int			m_iDieTime;

	// This pointer is to a valid VehicleInfo (which could be an animal, speeder, fighter, whatever). This
	// contains the functions actually used to do things to this specific kind of vehicle as well as shared
	// information (max speed, type, etc...).
	vehicleInfo_t *m_pVehicleInfo;

	// This trace tells us if we're within landing height.
	trace_t m_LandTrace;

	//bitflag of surfaces that have broken off
	int			m_iRemovedSurfaces;

	// the last time this vehicle fired a turbo burst
	int			m_iTurboTime;

	//how long it should drop like a rock for after freed from SUSPEND
	int			m_iDropTime;

	int			m_iSoundDebounceTimer;

	//last time we incremented the shields
	int			lastShieldInc;

	//so we don't hold it down and toggle it back and forth
	qboolean	linkWeaponToggleHeld;

	//info about our weapons (linked, ammo, etc.)
	vehWeaponStatus_t	weaponStatus[MAX_VEHICLE_WEAPONS];
	vehTurretStatus_t	turretStatus[MAX_VEHICLE_TURRETS];

	//the guy who was previously the pilot
	gentity_t*	m_pOldPilot;

	// don't need these in mp
	int			m_safeJumpMountTime;
	float		m_safeJumpMountRightDot;


    void sg_export(
        SgType& dst) const
    {
        ::sg_export(m_pPilot, dst.m_pPilot);
        ::sg_export(m_iPilotTime, dst.m_iPilotTime);
        ::sg_export(m_bHasHadPilot, dst.m_bHasHadPilot);
        ::sg_export(m_pDroidUnit, dst.m_pDroidUnit);
        ::sg_export(m_pParentEntity, dst.m_pParentEntity);
        ::sg_export(m_iBoarding, dst.m_iBoarding);
        ::sg_export(m_bWasBoarding, dst.m_bWasBoarding);
        ::sg_export(m_vBoardingVelocity, dst.m_vBoardingVelocity);
        ::sg_export(m_fTimeModifier, dst.m_fTimeModifier);
        ::sg_export(m_iLeftWingBone, dst.m_iLeftWingBone);
        ::sg_export(m_iRightWingBone, dst.m_iRightWingBone);
        ::sg_export(m_iExhaustTag, dst.m_iExhaustTag);
        ::sg_export(m_iMuzzleTag, dst.m_iMuzzleTag);
        ::sg_export(m_iDroidUnitTag, dst.m_iDroidUnitTag);
        ::sg_export(m_iGunnerViewTag, dst.m_iGunnerViewTag);
        ::sg_export(m_Muzzles, dst.m_Muzzles);
        ::sg_export(m_ucmd, dst.m_ucmd);
        ::sg_export(m_EjectDir, dst.m_EjectDir);
        ::sg_export(m_ulFlags, dst.m_ulFlags);
        ::sg_export(m_vOrientation, dst.m_vOrientation);
        ::sg_export(m_fStrafeTime, dst.m_fStrafeTime);
        ::sg_export(m_vPrevOrientation, dst.m_vPrevOrientation);
        ::sg_export(m_vAngularVelocity, dst.m_vAngularVelocity);
        ::sg_export(m_vFullAngleVelocity, dst.m_vFullAngleVelocity);
        ::sg_export(m_iArmor, dst.m_iArmor);
        ::sg_export(m_iShields, dst.m_iShields);
        ::sg_export(m_iLastFXTime, dst.m_iLastFXTime);
        ::sg_export(m_iDieTime, dst.m_iDieTime);
        ::sg_export(m_pVehicleInfo, dst.m_pVehicleInfo);
        ::sg_export(m_LandTrace, dst.m_LandTrace);
        ::sg_export(m_iRemovedSurfaces, dst.m_iRemovedSurfaces);
        ::sg_export(m_iTurboTime, dst.m_iTurboTime);
        ::sg_export(m_iDropTime, dst.m_iDropTime);
        ::sg_export(m_iSoundDebounceTimer, dst.m_iSoundDebounceTimer);
        ::sg_export(lastShieldInc, dst.lastShieldInc);
        ::sg_export(linkWeaponToggleHeld, dst.linkWeaponToggleHeld);
        ::sg_export(weaponStatus, dst.weaponStatus);
        ::sg_export(turretStatus, dst.turretStatus);
        ::sg_export(m_pOldPilot, dst.m_pOldPilot);
        ::sg_export(m_safeJumpMountTime, dst.m_safeJumpMountTime);
        ::sg_export(m_safeJumpMountRightDot, dst.m_safeJumpMountRightDot);
    }

    void sg_import(
        const SgType& src)
    {
        ::sg_import(src.m_pPilot, m_pPilot);
        ::sg_import(src.m_iPilotTime, m_iPilotTime);
        ::sg_import(src.m_bHasHadPilot, m_bHasHadPilot);
        ::sg_import(src.m_pDroidUnit, m_pDroidUnit);
        ::sg_import(src.m_pParentEntity, m_pParentEntity);
        ::sg_import(src.m_iBoarding, m_iBoarding);
        ::sg_import(src.m_bWasBoarding, m_bWasBoarding);
        ::sg_import(src.m_vBoardingVelocity, m_vBoardingVelocity);
        ::sg_import(src.m_fTimeModifier, m_fTimeModifier);
        ::sg_import(src.m_iLeftWingBone, m_iLeftWingBone);
        ::sg_import(src.m_iRightWingBone, m_iRightWingBone);
        ::sg_import(src.m_iExhaustTag, m_iExhaustTag);
        ::sg_import(src.m_iMuzzleTag, m_iMuzzleTag);
        ::sg_import(src.m_iDroidUnitTag, m_iDroidUnitTag);
        ::sg_import(src.m_iGunnerViewTag, m_iGunnerViewTag);
        ::sg_import(src.m_Muzzles, m_Muzzles);
        ::sg_import(src.m_ucmd, m_ucmd);
        ::sg_import(src.m_EjectDir, m_EjectDir);
        ::sg_import(src.m_ulFlags, m_ulFlags);
        ::sg_import(src.m_vOrientation, m_vOrientation);
        ::sg_import(src.m_fStrafeTime, m_fStrafeTime);
        ::sg_import(src.m_vPrevOrientation, m_vPrevOrientation);
        ::sg_import(src.m_vAngularVelocity, m_vAngularVelocity);
        ::sg_import(src.m_vFullAngleVelocity, m_vFullAngleVelocity);
        ::sg_import(src.m_iArmor, m_iArmor);
        ::sg_import(src.m_iShields, m_iShields);
        ::sg_import(src.m_iLastFXTime, m_iLastFXTime);
        ::sg_import(src.m_iDieTime, m_iDieTime);
        ::sg_import(src.m_pVehicleInfo, m_pVehicleInfo);
        ::sg_import(src.m_LandTrace, m_LandTrace);
        ::sg_import(src.m_iRemovedSurfaces, m_iRemovedSurfaces);
        ::sg_import(src.m_iTurboTime, m_iTurboTime);
        ::sg_import(src.m_iDropTime, m_iDropTime);
        ::sg_import(src.m_iSoundDebounceTimer, m_iSoundDebounceTimer);
        ::sg_import(src.lastShieldInc, lastShieldInc);
        ::sg_import(src.linkWeaponToggleHeld, linkWeaponToggleHeld);
        ::sg_import(src.weaponStatus, weaponStatus);
        ::sg_import(src.turretStatus, turretStatus);
        ::sg_import(src.m_pOldPilot, m_pOldPilot);
        ::sg_import(src.m_safeJumpMountTime, m_safeJumpMountTime);
        ::sg_import(src.m_safeJumpMountRightDot, m_safeJumpMountRightDot);
    }
};

extern int BG_VehicleGetIndex( const char *vehicleName );

#endif	// __G_VEHICLES_H
