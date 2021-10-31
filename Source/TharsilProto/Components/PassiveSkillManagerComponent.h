// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TharsilProto/CombatEffects/CombatAttributesSet.h"
#include "TharsilProto/ProgressionSystems/PassiveSkilltreeNodeTypes.h"
#include "PassiveSkillManagerComponent.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPassiveSkillEffect ThisSkillsEffect;

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

	EPassiveSkillEffect PassiveEffects;

	FDamageTypeBreakdown OffensivePassiveStats;

	FDamageResistanceBreakdown DefensivePassiveStats;

	//---------------------------------------------------------------------Variables that result from Skill Node Unlocks. 
	/// <summary>
	/// These are increased when the respective skill nodes are unlocked. e.g. unlocking a strength node will ++ the passiveSkillStrength variable. That gets called when calculating total strength.
	/// </summary>
	/// 
	


	// Main Attributes
	int32 PassiveSkillStrength = 0;
	int32 PassiveSkillAgility = 0;
	int32 PassiveSkillConstitution = 0;
	int32 PassiveSkillEndurance = 0;
	int32 PassiveSkillSpirit = 0;
	int32 PassiveSkillArcaneEssence = 0;

	// Seconary Attributes
	float BreathPassive = 0.0f;
	float CarryCapacityPassive = 0.0f;
	float HealthPointsPassive = 0.0f;
	float HealthRegenPassive = 0.0f;
	float StaminaPointsPassive = 0.0f;
	float StaminaRegenPassive = 0.0f;
	float ManaPointsPassive = 0.0f;
	
	
	//Direct Damage and status effect Attributes
	
	UCombatAttributesSet* PassiveCombatAttributes;

	//=========================OLD

	//OFFENSIVE MODIFICATIONS
	//Damage Modifiers
	int32 ArmorPenetrationPassive = 0;
	float Damage1hSlashPassive = 0.0f;
	float Damage1hPiercePassive = 0.0f;
	float Damage1hCrushPassive = 0.0f;
	float Damage2hSlashPassive = 0.0f;
	float Damage2hPiercePassive = 0.0f;
	float Damage2hCrushPassive = 0.0f;
	float DamageRangedSlashPassive = 0.0f;
	float DamageRangedPiercePassive = 0.0f;
	float DamageRangedCrushPassive = 0.0f;

	//Critical Modifiers
	float CriticalDamagePassive = 0.0f;
	float CriticalChancePassive = 0.0f;

	//Bleed Damage Modifiers
	float BleedChancePassive = 0.0f;
	float BleedDamagePassive = 0.0f;
	float BleedDurationPassive = 0.0f;

	//Physical Condition Modifiers
	float CrippleDurationPassive = 0.0f;
	float CrippleChancePassive = 0.0f;
	float KnockbackStrengthPassive = 0.0f;
	float KnockdownChancePassive = 0.0f;
	float StunChancePassive = 0.0f;
	float StunDurationPassive = 0.0f;
	float BlindDurationPassive = 0.0f;

	// Toxic Damage Modifiers
	float ToxicDmgPassive = 0.0f;
	float PoisonChancePassive = 0.0f;
	float PoisonDurationPassive = 0.0f;

	//Fire Damage Modifiers
	float FireDmgPassive = 0.0f;
	float BurnChancePassive = 0.0f;
	float BurnDurationPassive = 0.0f;

	//Cold Damage Modifiers
	float ColdDamagePassive = 0.0f;
	float ChillChancePassive = 0.0f;
	float ChillDurationPassive = 0.0f;
	float FreezeChancePassive = 0.0f;
	float FreezeDurationPassive = 0.0f;

	//Corrision Modifiers - Corrosion creates AP against the affected enemy
	float CorrosiveDamage = 0.0f;
	float CorrosionDuration = 0.0f;
	float PerCorrosionAP = 0.0f;

	//RESISTANCES AND DEFENSIVE MODIFICATIONS
	//Physical
	
	float SlashDefense = 0.0f;
	float PierceDefense = 0.0f;
	float CrushDefense = 0.0f;

	float KnockbackResist = 0.0f;
	float KnockdownResist = 0.0f;

	float ToxinResist = 0.0f;
	float OverheatResist = 0.0f;
	float FrostResist = 0.0f;
	float CorrosionResist = 0.0f;

	//Hard Damage Reduction
	float ReduceIncomingSlashDamagePassive = 0.0f;
	float ReduceIncomingPierceDamagePassive = 0.0f;
	float ReduceIncomingCrushDamagePassive = 0.0f;
	float DamageOnBlockReductionPassive = 0.0f;
	float DamageToArmorReductionPassive = 0.0f;
	float DamageToWeaponReductionPassive = 0.0f;

	//Pure Magical Resistances = Subject to removal.
	float LightningResist = 0.0f;
	float FaeResist = 0.0f;
	float NecroticResist = 0.0f;
	float AetherealResist = 0.0f;
	float DarknessResist = 0.0f;
	float LightResist = 0.0f;
	float BloodMagicResist = 0.0f;

	//DURATION REDUCTION
	float ChillSelfDurationReductionPassive = 0.0f;
	float BurnSelfDurationReductionPassive = 0.0f;
	float BlindSelfDurationReductionPassive = 0.0f;
	float CrippleSelfDurationReductionPassive = 0.0f;
	float StunSelfDurationReductionPassive = 0.0f;
	float BleedSelfDurationReductionPassive = 0.0f;

	//UTILITY AND CHARACTER IMPROVEMENTS
	//COST REDUCTION
	float AttackCostReductionPassive = 0.0f;
	float StanceCostReductionPassive = 0.0f;
	float ShoutCostReductionPassive = 0.0f;
	float SprintCostReductionPassive = 0.0f;
	float DodgeCostReductionPassive = 0.0f;

	//Speed
	float SprintSpeedPassive = 0.0f;

	//More to follow on system implementations


	//--------------------------------------------------------------------General SkillTree Functions -----------------------------------------------------------------

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

	//void IncreaseStatusChance(FStatusEffect StatusEffect, FPassiveSkillNode SkillNode);


	void AddAttributeAgility(FPassiveSkillNode SkillNode);
	void AddAttributeArcaneEssence(FPassiveSkillNode SkillNode);
	void AddAttributeArmorPenetration(FPassiveSkillNode SkillNode);
	void AddAttributeBreath(FPassiveSkillNode SkillNode);
	void AddAttributeCarryCapacity(FPassiveSkillNode SkillNode); 
	void AddAttributeConstitution(FPassiveSkillNode SkillNode);
	void AddAttributeEndurance(FPassiveSkillNode SkillNode);
	void AddAttributeHealth(FPassiveSkillNode SkillNode);
	void AddAttributeHealthRegen(FPassiveSkillNode SkillNode);
	void AddAttributeSpirit(FPassiveSkillNode SkillNode);
	void AddAttributeStamina(FPassiveSkillNode SkillNode);
	void AddAttributeStaminaRegen(FPassiveSkillNode SkillNode);
	void AddAttributeStrength(FPassiveSkillNode SkillNode);
	/*void AddDamage1hCrush(FPassiveSkillNode SkillNode);
	void AddDamage1hPierce(FPassiveSkillNode SkillNode);
	void AddDamage1hSlash(FPassiveSkillNode SkillNode);
	void AddDamage2hCrush(FPassiveSkillNode SkillNode);
	void AddDamage2hPierce(FPassiveSkillNode SkillNode);
	void AddDamage2hSlash(FPassiveSkillNode SkillNode);*/
	void AddDamageCritical(FPassiveSkillNode SkillNode);
/*	void AddDamageRangedCrush(FPassiveSkillNode SkillNode);
	void AddDamageRangedPierce(FPassiveSkillNode SkillNode);
	void AddDamageRangedSlash(FPassiveSkillNode SkillNode);
	void AddResistanceFrost(FPassiveSkillNode SkillNode);
	void AddChanceCripple(FPassiveSkillNode SkillNode);
	void AddResistanceOverheat(FPassiveSkillNode SkillNode);
	void AddResistanceKnockback(FPassiveSkillNode SkillNode);
	void AddResistancePoison(FPassiveSkillNode SkillNode);
	void AddChanceBleed(FPassiveSkillNode SkillNode);
	void AddDurationBleed(FPassiveSkillNode SkillNode);
	void AddDamageBleed(FPassiveSkillNode SkillNode);
	void AddDurationCripple(FPassiveSkillNode SkillNode);
	void AddChanceCritical(FPassiveSkillNode SkillNode);
	void ReduceDamageOnBlock(FPassiveSkillNode SkillNode);
	void AddStrengthKnockback(FPassiveSkillNode SkillNode);
	void AddChanceKnockdown(FPassiveSkillNode SkillNode); */
	void AddSpeedSprint(FPassiveSkillNode SkillNode);
/*	void AddDurationStun(FPassiveSkillNode SkillNode);
	void ReduceStaminaCostOnAttack(FPassiveSkillNode SkillNode);
	void ReduceStaminaCostOnDodge(FPassiveSkillNode SkillNode);
	void ReduceStaminaCostOnStance(FPassiveSkillNode SkillNode);
	void ReduceStaminaCostOnShout(FPassiveSkillNode SkillNode);
	void ReduceDurationStun(FPassiveSkillNode SkillNode);
	void ReduceDurationBleed(FPassiveSkillNode SkillNode);
	void ReduceDurationCripple(FPassiveSkillNode SkillNode);
	void AddDamageFire(FPassiveSkillNode SkillNode);
	void AddChanceBurn(FPassiveSkillNode SkillNode);
	void AddDurationBurn(FPassiveSkillNode SkillNode);
	void AddDamageToxic(FPassiveSkillNode SkillNode);
	void AddChancePoison(FPassiveSkillNode SkillNode);
	void AddDurationPoison(FPassiveSkillNode SkillNode);
	void AddDurationBlindness(FPassiveSkillNode SkillNode);
	void AddChanceStun(FPassiveSkillNode SkillNode); */
	void AddDamageFrost(FPassiveSkillNode SkillNode);
/*	void AddChanceChill(FPassiveSkillNode SkillNode);
	void AddDurationChill(FPassiveSkillNode SkillNode);
	void AddChanceFreeze(FPassiveSkillNode SkillNode);
	void AddDurationFreeze(FPassiveSkillNode SkillNode);
	void AddDamageCorrosive(FPassiveSkillNode SkillNode);
	void AddDurationCorrosive(FPassiveSkillNode SkillNode);
	void AddResistanceKnockdown(FPassiveSkillNode SkillNode);
	void AddDefenseSlash(FPassiveSkillNode SkillNode);
	void AddDefensePierce(FPassiveSkillNode SkillNode);
	void AddDefenseCrush(FPassiveSkillNode SkillNode);
	void AddArPePerCorrosion(FPassiveSkillNode SkillNode);
	void AddResistanceCorrosive(FPassiveSkillNode SkillNode);
	void ReduceDamageToArmor(FPassiveSkillNode SkillNode);
	void ReduceDamageToWeapon(FPassiveSkillNode SkillNode);
	void ReduceDurationChill(FPassiveSkillNode SkillNode);
	void ReduceDurationBurn(FPassiveSkillNode SkillNode);
	void ReduceDurationBlind(FPassiveSkillNode SkillNode);
	void ReduceStaminaCostSprint(FPassiveSkillNode SkillNode);
*/

};
