// Fill out your copyright notice in the Description page of Project Settings.

#include "BlogGameInstance.h"
#include "BlogSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LoadingUserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

UBlogGameInstance::UBlogGameInstance()
{
	//// 先检测是否有存档 
	//bool bRet = UGameplayStatics::DoesSaveGameExist(TEXT("HeroLocation"), 0);
	//if (bRet) // 如果有存档，则读取记录
	//{
	//	//SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
	//	SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HeroLocation"), 0));
	//	if (SaveGame)
	//	{
	//		HeroLocation = SaveGame->LastLocation; // 读取最后一次保存的位置
	//		bLoadGame = true;
	//	}
	//}
	//else // 没有 则先创建存档
	//{
	//	SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
	//	this->SaveGame = SaveGame;
	//	bLoadGame = false;
	//}

	// 硬引用
	static ConstructorHelpers::FClassFinder<UUserWidget> LoadingWidgetBP(TEXT("/Game/ThirdPersonCPP/UI/LoadingScreen"));
	if (LoadingWidgetBP.Succeeded())
	{
		LoadingWidget = LoadingWidgetBP.Class;
	}

}

// 加载地图中间显示
struct FHotBattleLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FHotBattleLoadingScreenBrush(const FName TextureName, const FVector2D& ImageSize)
		: FSlateDynamicImageBrush(TextureName, ImageSize)
	{
		ResourceObject = LoadObject<UObject>(NULL, *TextureName.ToString());
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (ResourceObject)
		{
			Collector.AddReferencedObject(ResourceObject);
		}
	}

};

class SHotBattleLoadingScreen : public SCompoundWidget // GetMoviePlayer必须使用swidget
{
public:
	SLATE_BEGIN_ARGS(SHotBattleLoadingScreen) : _NowLevel() {}
	SLATE_ARGUMENT(NowLevel::type, NowLevel) // 使用这个宏后就有了_NowLevel变量
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs)
	{
		NowLevelIn = InArgs._NowLevel; // 获取当前处于哪个关卡，加载相应的背景图在这使用_NowLevel变量
		FString text;

		FName LoadingScreenName;
		switch (NowLevelIn)
		{
		case NowLevel::INITIAL:
			LoadingScreenName = TEXT("/Game/ThirdPersonCPP/UI/Res/Initialize");
			text = FString(TEXT("Initialize"));
			break;
		case NowLevel::LEVELONE:
			LoadingScreenName = TEXT("/Game/ThirdPersonCPP/UI/Res/Ice");
			text = FString(TEXT("LevelOne"));
			break;
		}

		LoadingScreenBrush = MakeShareable(new FHotBattleLoadingScreenBrush(LoadingScreenName, FVector2D(1920, 1080)));

		ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(text))
			]
			];
	}

private:
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
	NowLevel::type NowLevelIn;
};

void UBlogGameInstance::Init()
{
	Super::Init();
	// 先检测是否有存档 
	bool bRet = UGameplayStatics::DoesSaveGameExist(TEXT("HeroLocation"), 0);
	if (bRet) // 如果有存档，则读取记录
	{
		//SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
		SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HeroLocation"), 0));
		if (SaveGame)
		{
			HeroLocation = SaveGame->LastLocation; // 读取最后一次保存的位置
			bLoadGame = true;
		}
	}
	else // 没有 则先创建存档
	{
		SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
		bLoadGame = false;
	}

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBlogGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UBlogGameInstance::EndLoadingScreen);

	CurrentLevel = NowLevel::INITIAL;

	return;
}

void UBlogGameInstance::BeginLoadingScreen(const FString& MapName)
{
	//if (LoadingWidget != nullptr)
	//{
	//	APlayerController* AC = GetWorld()->GetFirstPlayerController();
	//	UE_LOG(LogTemp, Warning, TEXT("NewWidget: %s"), *(AC->GetName()));
	//	ULoadingUserWidget* NewWidget = CreateWidget<ULoadingUserWidget>(AC, LoadingWidget);
	//	//UE_LOG(LogTemp, Warning, TEXT("NewWidget: %s"), *(NewWidget->GetName()));
	//	if (NewWidget != nullptr)
	//	{
	//		switch (CurrentLevel)
	//		{
	//		case NowLevel::INITIAL:
	//			NewWidget->SetLevel(0);
	//			break;
	//		case NowLevel::LEVELONE:
	//			NewWidget->SetLevel(1);
	//			break;
	//		default:
	//			break;
	//		}
	//		// 创建加载界面参数
	//		if (!IsRunningDedicatedServer())
	//		{
	//			FLoadingScreenAttributes attr;
	//			attr.bAutoCompleteWhenLoadingCompletes = true;
	//			attr.WidgetLoadingScreen = NewWidget->TakeWidget();
	//		}

	//	}
	//}

	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		//LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget(); // 使用自定义的loadscreen的话必须是slate

		LoadingScreen.WidgetLoadingScreen = SNew(SHotBattleLoadingScreen).NowLevel(CurrentLevel); // 加载地图时使用该背景

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

}

void UBlogGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{

}




