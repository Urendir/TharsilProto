// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TharsilProto/CombatEffects/CombatAttributesSet.h"
#include "TharsilProto/ProgressionSystems/GeneralAttributeSet.h"
#include "TharsilProto/ProgressionSystems/PassiveSkilltreeNodeTypes.h"
#include "PassiveSkillManagerComponent.generated.h"



UENUM(BlueprintType, Category="SkillNode Description")
enum class EAffectedAttributeType : uint8
{
	E_NoAffectedAttribute	UMETA(DisplayName = "No Attribute Affected"),
	E_EnergyAttribute		UMETA(DisplayName = "Energy Attribute"),
	E_MainAttribute			UMETA(DisplayName = "Main Attribute"),
	E_GeneralAttribute		UMETA(DisplayName = "General Attribute"),
	E_PhysicalDamage		UMETA(DisplayName = "Physical Damage"),
	E_ElementalDamage		UMETA(DisplayName = "Elemental Damage"),
	E_StatusEffect			UMETA(DisplayName = "Status Effect"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EEnergyAttributeType : uint8
{
	NotEnergy 		UMETA(DisplayName = "Not Energy"),
	Health			UMETA(DisplayName = "Health"),
	Stamina			UMETA(DisplayName = "Stamina"),
	Mana			UMETA(DisplayName = "Mana"),
	Breath			UMETA(DisplayName = "Breath"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EEnergyAttributeDescriptor : uint8
{
	NotEnergy 		UMETA(DisplayName = "Not Energy"),
	MaxValue		UMETA(DisplayName = "Maximum Value"),
	RegenRate		UMETA(DisplayName = "Regeneration Rate"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EMainAttributeType : uint8
{
	NotMain 		UMETA(DisplayName = "Not Main Attribute"),
	Strength		UMETA(DisplayName = "Strength"),
	Agility			UMETA(DisplayName = "Agility"),
	Endurance		UMETA(DisplayName = "Endurance"),
	Constitution	UMETA(DisplayName = "Constitution"),
	ArcaneEssence	UMETA(DisplayName = "Arcane Essence"),
	Spirit			UMETA(DisplayName = "Spirit"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EGeneralAttributeType : uint8
{
	NotGeneral 		UMETA(DisplayName = "Not General Attribute"),
	CriticalChance		UMETA(DisplayName = "Crit Chance"),
	CritDamage			UMETA(DisplayName = "Crit Damage"),
	OneHandAttackCost		UMETA(DisplayName = "1h Attack Cost"),
	TwoHandAttackCost	UMETA(DisplayName = "2H Attack Cost"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EPhysicalDamageType : uint8
{
	NotPhysical 	UMETA(DisplayName = "Not Physical"),
	Crush			UMETA(DisplayName = "Crush Damage"),
	Pierce			UMETA(DisplayName = "Pierce Damage"),
	Slash			UMETA(DisplayName = "Slash Damage"),
	ArmorPen		UMETA(DisplayName = "Armor Penetration"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EPhysicalDamageSpecific : uint8
{
	NotPhysical 	UMETA(DisplayName = "Not Physical"),
	OneHand			UMETA(DisplayName = "One-Hand Damage"),
	TwoHand			UMETA(DisplayName = "Two-Hand Damage"),
	Ranged			UMETA(DisplayName = "Ranged Damage"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EElementalDamageType : uint8
{
	E_NotElemental	UMETA(DisplayName = "Not Elemental"),
	E_Bleed			UMETA(DisplayName = "Bleed"),
	E_Fire			UMETA(DisplayName = "Fire"),
	E_Cold			UMETA(DisplayName = "Cold"),
	E_Toxic			UMETA(DisplayName = "Toxic"),
	E_Corrosive		UMETA(DisplayName = "Corrosive"),
	E_Blind			UMETA(DisplayName = "Blind"),
	E_Weak			UMETA(DisplayName = "Weaken"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EStatusEffectType : uint8
{
	E_NotStatus		UMETA(DisplayName = "Not Status"),
	E_Bleeding		UMETA(DisplayName = "Bleeding"),
	E_Overheating	UMETA(DisplayName = "Overheating"),
	E_Burning		UMETA(DisplayName = "Burning"),
	E_Chilled		UMETA(DisplayName = "Chilled"),
	E_Freezing		UMETA(DisplayName = "Freezing"),
	E_Poison		UMETA(DisplayName = "Poison"),
	E_Necrosis		UMETA(DisplayName = "Necrosis"),
	E_Corrosion		UMETA(DisplayName = "Corrosion"),
	E_Blinding		UMETA(DisplayName = "Blinding"),
	E_Weakening		UMETA(DisplayName = "Weakening"),
	E_Stun			UMETA(DisplayName = "Stun"),
	E_Knockdown		UMETA(DisplayName = "KnockDown"),
	E_Cripple		UMETA(DisplayName = "Cripple"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EAffectedTarget : uint8
{
	E_Self				UMETA(DisplayName = "Self"),
	E_Target			UMETA(DisplayName = "Target"),
};

UENUM(BlueprintType, Category = "SkillNode Description")
enum class EAffectedDescriptor : uint8
{
	E_NoDescriptor		UMETA(DisplayName = "Not Status Type"),
	E_DamageOnTick		UMETA(DisplayName = "Damage on Tick"),
	E_Duration			UMETA(DisplayName = "Duration"),
	E_Chance			UMETA(DisplayName = "Chance"),
};




USTRUCT(BlueprintType)
struct FPassiveSkillNode : public FTableRowBase
{
	GENERATED_BODY()
	

	//---------------------------------------------------This is pulled from the Data Table to allow for position and the neighbour assignment. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UniqueNodeID;

	//----------------------------------------------------Descriptions
	
	//the Name of the Node.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NodeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NodeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AssignmentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsValueInPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsSkillNodeByDefaultReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSkillNodeReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSkillNodePurchased;

	/*Select this to determine the attribute type*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAffectedAttributeType AttributeType;
	/*What Energy Attribute is changed? Relevant if Attribute Type is Energy. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnergyAttributeType EnergyAttribute;
	/*What is changed on the Energy Attribute? Relevant if Attribute Type is Energy. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnergyAttributeDescriptor EnergyAttributeElement;
	/*Relevant if Attribute Type is Main. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMainAttributeType MainAttribute;
	/*Which general attribute is being changed? Relevant if Attribute Type is General. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGeneralAttributeType GeneralAttribute;
	/*What type of Physical damage is being affected? Only relevant if the Attribute Type is Physical. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPhysicalDamageType PhysicalDamageType;
	/*Allows to select between specific weapontypes for damage calculation. Only relevant if the Attribute Type is Physical. Otherwise, ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPhysicalDamageSpecific SpecificPhysicalDamage;
	/*What type of Elemental damage is being affected? Only relevant if the Attribute Type is Elemental. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EElementalDamageType ElementalDamageType;
	/*Which Status Effect is being affected? Only relevant if the Attribute Type is Status Effect. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStatusEffectType StatusEffectType;
	/*Which element of the status effect is changed? Relevant for StatusEffects only. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAffectedDescriptor AffectedSatusEffectDescriptor;
	/*Relevant for Type Physical, Elemental, Status. Otherwise, ignored.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAffectedTarget	AffectedTarget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NeighbourNodes;

	//----------------------------------------------------Skill Node Icons. Can be set on Initialization to allow for player affordance in widget.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconLocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconPurchased;
};


class ABaseCharacterPlayable;
class UPassiveSkillNode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UPassiveSkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveSkillManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int32 AvailableSkillpoints = 10;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ABaseCharacterPlayable* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FPassiveSkillNode> SkillTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* PassiveSkillNodesTable;

	//OBSOLETE EPassiveSkillEffect PassiveEffects; OBSOLETE

	//OBSOLETE FDamageTypeBreakdown OffensivePassiveStats;OBSOLETE

	//OBSOLETE FDamageResistanceBreakdown DefensivePassiveStats;OBSOLETE

	//---------------------------------------------------------------------Variables that result from Skill Node Unlocks. 
	/// <summary>
	/// These are increased when the respective skill nodes are unlocked. e.g. unlocking a strength node will ++ the passiveSkillStrength variable. That gets called when calculating total strength.
	/// </summary>
	/// 
	
	
	//Direct Damage and status effect Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGeneralAttributeSet* PassiveAttributes;



	/////
	/////============================================OLD VALUES==============================================
	///// 
	///// 
	///// 
	//// Main Attributes
	//int32 PassiveSkillStrength = 0;
	//int32 PassiveSkillAgility = 0;
	//int32 PassiveSkillConstitution = 0;
	//int32 PassiveSkillEndurance = 0;
	//int32 PassiveSkillSpirit = 0;
	//int32 PassiveSkillArcaneEssence = 0;
	//// Seconary Attributes
	//float BreathPassive = 0.0f;
	//float CarryCapacityPassive = 0.0f;
	//float HealthPointsPassive = 0.0f;
	//float HealthRegenPassive = 0.0f;
	//float StaminaPointsPassive = 0.0f;
	//float StaminaRegenPassive = 0.0f;
	//float ManaPointsPassive = 0.0f;
	////=========================OLD
	////OFFENSIVE MODIFICATIONS
	////Damage Modifiers
	//int32 ArmorPenetrationPassive = 0;
	//float Damage1hSlashPassive = 0.0f;
	//float Damage1hPiercePassive = 0.0f;
	//float Damage1hCrushPassive = 0.0f;
	//float Damage2hSlashPassive = 0.0f;
	//float Damage2hPiercePassive = 0.0f;
	//float Damage2hCrushPassive = 0.0f;
	//float DamageRangedSlashPassive = 0.0f;
	//float DamageRangedPiercePassive = 0.0f;
	//float DamageRangedCrushPassive = 0.0f;
	////Critical Modifiers
	//float CriticalDamagePassive = 0.0f;
	//float CriticalChancePassive = 0.0f;
	////Bleed Damage Modifiers
	//float BleedChancePassive = 0.0f;
	//float BleedDamagePassive = 0.0f;
	//float BleedDurationPassive = 0.0f;
	////Physical Condition Modifiers
	//float CrippleDurationPassive = 0.0f;
	//float CrippleChancePassive = 0.0f;
	//float KnockbackStrengthPassive = 0.0f;
	//float KnockdownChancePassive = 0.0f;
	//float StunChancePassive = 0.0f;
	//float StunDurationPassive = 0.0f;
	//float BlindDurationPassive = 0.0f;
	//// Toxic Damage Modifiers
	//float ToxicDmgPassive = 0.0f;
	//float PoisonChancePassive = 0.0f;
	//float PoisonDurationPassive = 0.0f;
	////Fire Damage Modifiers
	//float FireDmgPassive = 0.0f;
	//float BurnChancePassive = 0.0f;
	//float BurnDurationPassive = 0.0f;
	////Cold Damage Modifiers
	//float ColdDamagePassive = 0.0f;
	//float ChillChancePassive = 0.0f;
	//float ChillDurationPassive = 0.0f;
	//float FreezeChancePassive = 0.0f;
	//float FreezeDurationPassive = 0.0f;
	////Corrision Modifiers - Corrosion creates AP against the affected enemy
	//float CorrosiveDamage = 0.0f;
	//float CorrosionDuration = 0.0f;
	//float PerCorrosionAP = 0.0f;
	////RESISTANCES AND DEFENSIVE MODIFICATIONS
	////Physical
	//
	//float SlashDefense = 0.0f;
	//float PierceDefense = 0.0f;
	//float CrushDefense = 0.0f;
	//float KnockbackResist = 0.0f;
	//float KnockdownResist = 0.0f;
	//float ToxinResist = 0.0f;
	//float OverheatResist = 0.0f;
	//float FrostResist = 0.0f;
	//float CorrosionResist = 0.0f;
	////Hard Damage Reduction
	//float ReduceIncomingSlashDamagePassive = 0.0f;
	//float ReduceIncomingPierceDamagePassive = 0.0f;
	//float ReduceIncomingCrushDamagePassive = 0.0f;
	//float DamageOnBlockReductionPassive = 0.0f;
	//float DamageToArmorReductionPassive = 0.0f;
	//float DamageToWeaponReductionPassive = 0.0f;
	////Pure Magical Resistances = Subject to removal.
	//float LightningResist = 0.0f;
	//float FaeResist = 0.0f;
	//float NecroticResist = 0.0f;
	//float AetherealResist = 0.0f;
	//float DarknessResist = 0.0f;
	//float LightResist = 0.0f;
	//float BloodMagicResist = 0.0f;
	////DURATION REDUCTION
	//float ChillSelfDurationReductionPassive = 0.0f;
	//float BurnSelfDurationReductionPassive = 0.0f;
	//float BlindSelfDurationReductionPassive = 0.0f;
	//float CrippleSelfDurationReductionPassive = 0.0f;
	//float StunSelfDurationReductionPassive = 0.0f;
	//float BleedSelfDurationReductionPassive = 0.0f;
	////UTILITY AND CHARACTER IMPROVEMENTS
	////COST REDUCTION
	//float AttackCostReductionPassive = 0.0f;
	//float StanceCostReductionPassive = 0.0f;
	//float ShoutCostReductionPassive = 0.0f;
	//float SprintCostReductionPassive = 0.0f;
	//float DodgeCostReductionPassive = 0.0f;
	////Speed
//float SprintSpeedPassive = 0.0f;
	////More to follow on system implementations


	//--------------------------------------------------------------------General SkillTree Functions -----------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void InitializePassiveAttributes();

	//Called on LevelUp or Skilltree Reset.
	UFUNCTION(BlueprintCallable)
	void IncreasePassiveSkillPoints();

	//Used to check for the number of points - used in widget. 
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentPassiveSkillPoints();

	//when a node is purchased, all neighbouring ones are set to reached, so they can be purchased after.
	UFUNCTION(BlueprintCallable)
	void ReachSkillNode(FPassiveSkillNode SkillNode);

	//unlocks the benefit of the node. 
	UFUNCTION(BlueprintCallable)
	void PurchaseSkillNode(FPassiveSkillNode SkillNode);

	//On Node purchase, calls Reach Skill Node on all nodes with uniqueID present in the array of neighbours of the purchased node. 
	UFUNCTION(BlueprintCallable)
	TArray<int32> ReachNeighbourNodes(FPassiveSkillNode SkillNode);

	//Used on skilltree reset. 
	UFUNCTION(BlueprintCallable)
	void ResetSkillNodeState(FPassiveSkillNode SkillNode);
	
	/// <summary>
	/// This Is a Main Switch statement for all skill Node types. 
	/// When a skillnode is purchased, the switch is cross-Referencing the NodeType Struct and deciding which passive-variable-impacting function to call.
	/// Having one function in the node purchase allows for better modularity. 
	/// </summary>
	void ProvideSkillNodeBonus(FPassiveSkillNode SkillNode);


private:
	// ==============================================Note for refactoring:
	// Main Attribute: Hard Value
	// Energy Attribute: Cost on Skill, Cost on Sprint, Hard Value, Regen Rate.
	// Physical Dmg: Damage, Resistance
	// SkillType: Reduce cost, Damage
	// Elemental Dmg: Damage, Resistance
	// Status Effect: Damage, Resistance, Chance, Duration

	//New functions related to Skillnote attributes
	UFUNCTION(BlueprintCallable)
	void ModifyEnergyAttribute(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	FEnergyAttribute DetermineEnergyAttributeToIncrease(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void IncreaseEnergyAttributeMaxValue(float AssignmentValue, FEnergyAttribute AttributeToIncrease);
	UFUNCTION(BlueprintCallable)
	void IncreaseEnergyAttributeRegenRate(float AssignmentValue, FEnergyAttribute AttributeToIncrease);
	UFUNCTION(BlueprintCallable)
	FMainAttribute DetermineMainAttributeToIncrease(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void IncreaseMainAttributeValue(float AssignmentValue, FMainAttribute AttributeToUpdate);
	//This function checks whether the Attribute is referring to offensive or defensive traits. E.g. physical damage or defense, elemental damage or resistance. 
	//It is reused in multiple Functions as variable for if statements.
	UFUNCTION(BlueprintCallable)
	bool AttributeTargetIsSelf(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	FPhysicalDamage DeterminePhysicalCombatStyleToUpdate(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void IncrementPhysicalDamage(FPassiveSkillNode SkillNode, FPhysicalDamage StyleToUpdate);
	UFUNCTION(BlueprintCallable)
	void IncrementPhysicalResistance(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void ModifyPhysicalAttributeValue(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void ModifyElementalDamageAttribute(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	FElementalDamage DetermineElementalDamageTypeToModify(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void IncrementElementalDamageOnTarget(FPassiveSkillNode SkillNode, FElementalDamage ElementToUpdate);
	UFUNCTION(BlueprintCallable)
	void DecrementElementalDamageOnSelf(FPassiveSkillNode SkillNode, FElementalDamage ElementToUpdate);
	UFUNCTION(BlueprintCallable)
	FStatusEffect DetermineStatusEffectToModify(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void ModifyStatusEffectBasedOnSelection(FPassiveSkillNode SkillNode);
	UFUNCTION(BlueprintCallable)
	void IncrementStatusDmgOnTick(float AssignmentValue, FStatusEffect StatusEffectToUpdate);
	UFUNCTION(BlueprintCallable)
	void DecrementStatusDmgTakenOnTick(float AssignmentValue, FStatusEffect StatusEffectToUpdate);
	UFUNCTION(BlueprintCallable)
	void IncrementStatusChanceOnTarget(float AssignmentValue, FStatusEffect StatusEffectToUpdate);
	UFUNCTION(BlueprintCallable)
	void DecrementStatusChanceOnSelf(float AssignmentValue, FStatusEffect StatusEffectToUpdate);
	UFUNCTION(BlueprintCallable)
	void IncrementStatusDurationOnTarget(float AssignmentValue, FStatusEffect StatusEffectToUpdate);
	UFUNCTION(BlueprintCallable)
	void DecrementStatusDurationOnSelf(float AssignmentValue, FStatusEffect StatusEffectToUpdate);



};
