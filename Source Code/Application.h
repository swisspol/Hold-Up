/***************************************************************************** * Copyright (c) 1999-2002, Pierre-Olivier Latour * http://www.pol-online.net * info@pol-online.net * * This program is free software; you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation; either version 2 of the License, or * (at your option) any later version. *  * This program is distributed in the hope that it will be useful, * but WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the * GNU General Public License for more details. * * You should have received a copy of the GNU General Public License * along with this program; if not, write to the Free Software * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA. *****************************************************************************/#ifndef __APPLICATION__#define __APPLICATION__//Constants#define		kApplication_CName				"Hold-Up"#define		kApplication_PName				"\p" kApplication_CName#define		kApplication_Creator			'HdUp'#define		kUndefinedID					0#define		kUndefinedNum					(-1)#define		kAutomatic_RepetitionType_Daily		'daly'#define		kAutomatic_RepetitionType_Monthly	'mnty'#define		kAutomatic_RepetitionType_Quarterly	'qtry'#if __DEMO__#define		kApplication_MaxAccounts		2#define		kApplication_MaxFilters			5#elif __BASIC__#define		kApplication_MaxAccounts		1#define		kApplication_MaxFilters			5#define		kSNMagic						kMagic_Basic#else#define		kApplication_MaxAccounts		64#define		kApplication_MaxFilters			64#define		kSNMagic						kMagic_Pro#endif#define		kMiscStringResID				129#define		kWindowStringsID				130#define		kColumnStringsID				131#define		kMenuIDOffset					128#define		kAboutDialogID					200#define		kSkinStartResID					128#define		kMaxFileNameChars				31#define		kSkipFileChar					'_'#define		kReturnChar						'\r'#define		kTabChar						'\t'#define		kNoteReturnChar					' '#define		kNewLineChar					'\n'enum {	kAppleMenu = 0,	kFileMenu,	kEditMenu,	kDisplayMenu,	kAccountMenu,	kNumMenus};#define		kCategoryMenuID					305#define		kPaymentMenuID					306#define		kFontMenuID						309#define		kAccountMenuID					310#define		kMacroMenuID					311#define		kAmountPrecision				2#define		kCurrencyFactorPrecision		6#define		kMesurePrecision				2//Typedefstypedef unsigned long ID;typedef unsigned long Date;typedef OSType Command;typedef void* CommandDataPtr;typedef long FixedReal;typedef FixedReal Amount;typedef FixedReal CurrencyFactor;typedef FixedReal Mesure;//Structures#if PRAGMA_STRUCT_ALIGN    #pragma options align=mac68k#elif PRAGMA_STRUCT_PACKPUSH    #pragma pack(push, 2)#elif PRAGMA_STRUCT_PACK    #pragma pack(2)#endiftypedef struct {	ID				id;	Str63			name;} PaymentType;typedef PaymentType* PaymentTypePtr;typedef struct {	short			fill;	unsigned short	count;	PaymentType		list[];} PaymentList;typedef PaymentList* PaymentListPtr;typedef struct {	ID				id;	Str63			name;	RGBColor		color;} Category;typedef Category* CategoryPtr;typedef struct {	short			fill;	unsigned short	count;	Category		list[];} CategoryList;typedef CategoryList* CategoryListPtr;typedef struct {	Str63			name;	long			unused;	CurrencyFactor	factor;} Macro;typedef Macro* MacroPtr;typedef struct {	short			fill;	unsigned short	count;	Macro			list[];} MacroList;typedef MacroList* MacroListPtr;#if PRAGMA_STRUCT_ALIGN    #pragma options align=reset#elif PRAGMA_STRUCT_PACKPUSH    #pragma pack(pop)#elif PRAGMA_STRUCT_PACK    #pragma pack()#endif//Fake declarationstypedef struct Preferences Preferences;typedef struct CommandServer CommandServer;typedef struct Account Account;typedef struct ErrorManager ErrorManager;typedef struct Operation Operation;typedef struct Filter Filter;typedef struct WindowServer WindowServer;typedef struct PrintServer PrintServer;typedef struct OperationSelection OperationSelection;//Classesclass Application{public:	Preferences*		prefs;	CommandServer*		commandServer;	ErrorManager*		errorManager;	WindowServer*		windowServer;	PrintServer*		printServer;		short				resFileID;	MenuHandle			menus[kNumMenus];#if __CARBON_EVENTS__	EventLoopTimerRef	timerRef;#else	Boolean				run;#endif	Date				today;		long				accountCount;	Account*			accountList[kApplication_MaxAccounts];	long				filterCount;	Filter*				filterList[kApplication_MaxFilters];	private:	ID					_idGenerator;#if !__CARBON_EVENTS__	EventRecord			_event;#endif	private:#if __CARBON_EVENTS__	OSStatus _CarbonHandleMouseDown();#endif	OSErr _InstallMenuBar();	OSErr _NewAccountFromFile(FSSpec* file);	OSErr _NewFilterFromFile(FSSpec* file);	long _ImportTabulatedText(Account* account, Ptr data, long size, long* idCount, ID idList[]);	long _ImportQIF(Account* account, Ptr data, long size, long* idCount, ID idList[]);	OSErr _ExportTabulatedText(short fileID);	OSErr _ExportQIF(short fileID);public:#if __CARBON_EVENTS__	OSStatus CarbonApplicationEventHandler(EventRef event);	OSStatus CarbonWindowEventHandler(EventRef event);#else	void ClassicEventLoop();#endif	void Idle();	OSErr NewAccountFromUser();	OSErr NewFilterFromUser();	Boolean DeleteAccount(long num);	Boolean DeleteFilter(long num);	void SortAccountsAlphabetically();	void SortFiltersAlphabetically();	OSErr WriteAccountToDisk(Account* account);	OSErr WriteFilterToDisk(Filter* filter);	Boolean WriteAllToDisk();		ID GenerateUniqueID();		void SynchronizeMenus();	void ShowAbout(short resID);	OSErr ExportOperations();	OSErr ImportOperations();	Boolean EditMultipleOperations(OperationSelection* selection);		long AutoCompleteDescription(Str63 text);	Application();	~Application();};typedef Application* ApplicationPtr;//Macros#define	MenuNumToID(n) (kMenuIDOffset + (n))#define	MenuIDToNum(id) ((id) - kMenuIDOffset)//Accessors#define	appPrefs (application->prefs->data)//Variablesextern ApplicationPtr		application;extern ModalFilterUPP		ModalDialogRoutine;extern Boolean				dialogCharReceived;extern EventRecord			lastModalDialogEvent;#endif //__APPLICATION__