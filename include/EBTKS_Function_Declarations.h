//
//	06/27/2020	These Function Declarations were moved from EBTKS.cpp to here.
//

//
//  1MB5/disk functions
//
void initTranslator(int selectNum);
void loopTranslator(void);
uint8_t get_Select_Code(void);

//
//  bank rom functions
//
uint8_t getRselec(void);
uint8_t *getRomSlotPtr(int slotNum);
void initRoms(void);
void setRomMap(uint8_t romId,uint8_t slotNum);

//
//  Tape functions
//
bool tape_handle_MOUNT(char *path);
void tape_handle_UNMOUNT(void);
void report_media(void);             // does both tape and disk

//
//  DMA Functions
//

int32_t DMA_Read_Block(uint32_t DMA_Target_Address, uint8_t buffer[], uint32_t bytecount);
int32_t DMA_Write_Block(uint32_t DMA_Target_Address, uint8_t buffer[], uint32_t bytecount);

uint8_t  DMA_Peek8 (uint32_t address);
uint16_t DMA_Peek16(uint32_t address);

void    DMA_Poke8 (uint32_t address, uint8_t  val);
void    DMA_Poke16(uint32_t address, uint16_t val);


//
//  CRT Functions
//
void initCrtEmu();
void dumpCrtAlpha(void);
void Write_on_CRT_Alpha(uint16_t row, uint16_t column, const char *  text);
void dumpCrtAlphaAsBase64(char *buff, bool comp_graph);
void writePixel(int x, int y, int color);
void writeLine(int x0, int y0, int x1, int y1, int color);
void CRT_capture_screen(void);
void CRT_restore_screen(void);
void Send_Visible_CRT_to_Serial(void);
void Send_All_CRT_to_Serial(void);

//
//  Bank Switched ROM support
//
bool      readBankRom(uint16_t addr);
uint8_t * getROMEntry(uint8_t romId);

//
//  HP-85 Bus interface and ISR functions
//

void assert_DMA_Request(void);
void release_DMA_request(void);
FASTRUN void pinChange_isr(void) __attribute__ ((interrupt ("IRQ")));     //  This fixed the keyboard random errors, which was caused by unsaved registers on interrupt
                                                                          //  not being saved by normal function entry          #####
void setupPinChange(void);
void mySystick_isr(void);
void initIOfuncTable(void);
void setIOReadFunc(uint8_t addr,ioReadFuncPtr_t readFuncP);
void setIOWriteFunc(uint8_t addr,ioWriteFuncPtr_t writeFuncP);
void removeIOReadFunc(uint8_t addr);
void removeIOWriteFunc(uint8_t addr);



//
//  SD Card support
//
bool loadRom(const char *fname, int slotNum, const char * description);
bool loadConfiguration(const char *filename);
bool remount_drives(const char *filename);
//  void printDirectory(FsFile dir, int numTabs);
void no_SD_card_message(void);
void dump_SD_Card_Info(void);
void diag_dir_path(const char * path);

//
//  HP85 16k exp ram
//
void enHP85RamExp(bool en);
bool getHP85RamExp(void);

bool LineAtATime_ls_Init_SDCAT(char * path);
bool LineAtATime_ls_Next_SDCAT(void);
bool LineAtATime_ls_Init_SDDEL(char * path);
bool LineAtATime_ls_Next_SDDEL(void);

//
//  Log File support
//

bool open_logfile(void);
void append_to_logfile(const char * text);
void flush_logfile(void);
void close_logfile(void);
void show_logfile(void);
void clean_logfile(void);

//
//  AUXROM Support functions
//

void ioWriteAuxROM_Alert(uint8_t val);
bool onReadAuxROM_Alert(void);
void AUXROM_Poll(void);
void AUXROM_Fetch_Memory(uint8_t * dest, uint32_t src_addr, uint16_t num_bytes);
void AUXROM_Store_Memory(uint16_t dest_addr, char * source, uint16_t num_bytes);
void AUXROM_Fetch_Parameters(void * Parameter_Block_XXX , uint16_t num_bytes);
double cvt_HP85_real_to_IEEE_double(uint8_t number[]);
int32_t cvt_R12_int_to_int32(uint8_t number[]);
//void cvt_int32_to_HP85_tagged_integer(uint8_t * dest, int val);
void cvt_IEEE_double_to_HP85_number(uint8_t * dest, double val);
bool Resolve_Path(char *New_Path);
void post_custom_error_message(const char * message, uint16_t error_number);
void post_custom_warning_message(const char * message, uint16_t error_number);

//
//  AUXROM Functions/Keywords/Statements
//

void initialize_SD_functions(void);

void AUXROM_DATETIME(void);
void AUXROM_FLAGS(void);
void AUXROM_HELP(void);
void AUXROM_SDCAT(void);
void AUXROM_SDCD(void);
void AUXROM_SDCLOSE(void);
void AUXROM_SDCUR(void);
void AUXROM_SDDEL(void);
void AUXROM_SDFLUSH(void);
void AUXROM_MEDIA(void);
void AUXROM_SDMKDIR(void);
void AUXROM_MOUNT(void);
void AUXROM_SDOPEN(void);
void AUXROM_SPF(void);
void AUXROM_SDREAD(void);
void AUXROM_SDREN(void);
void AUXROM_SDRMDIR(void);
void AUXROM_SDSEEK(void);
void AUXROM_SDWRITE(void);
void AUXROM_UNMOUNT(void);
void AUXROM_WROM(void);
          void AUXROM_MEMCPY(void);     //  #### Not yet implemented, is it needed? Does anything use it?
void AUXROM_SETLED(void);
void AUXROM_SDCOPY(void);
void AUXROM_SDEOF(void);
void AUXROM_SDEXISTS(void);
void AUXROM_EBTKSREV(void);
void AUXROM_RMIDLE(void);
void AUXROM_SDBATCH(void);
void AUXROM_BOOT(void);

//
//  Utility Functions
//

void SCOPE_1_Pulser(uint8_t count);

void EBTKS_delay_ns(int32_t count);

bool wait_for_serial_string(void);
void get_serial_string_poll(void);
void serial_string_used(void);

void Serial_Command_Poll(void);

void str_tolower(char *p);
bool MatchesPattern(char *pT, char *pP);
void HexDump_T41_mem (uint32_t start_address, uint32_t count, bool show_addr, bool final_nl);
void HexDump_HP85_mem(uint32_t start_address, uint32_t count, bool show_addr, bool final_nl);
void show_mailboxes_and_usage(void);

time_t getTeensy3Time(void);
void show_RTC(void);

void ESP_Programmer_Setup(void);
void ESP_Reset(void);

//void show_file(void);

void Setup_Logic_Analyzer(void);
void Logic_analyzer_go(void);
void Logic_Analyzer_Poll(void);

void Simple_Graphics_Test(void);

//void WS2812_init(void);
void setLedColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void WS2812_update(void);
void initialize_RMIDLE_processing(void);
void load_text_for_RMIDLE(char * text);
bool open_RMIDLE_file(char * SD_filename);

int int_power(int base, int exp);

//
//  various configuration stuff
//
int  get_machineNum(void);
char * get_machineType(void);
bool get_CRTVerbose(void);
bool get_screenEmu(void);
bool get_CRTRemote(void);
bool get_AutoStartEn(void);
bool get_TapeEn(void);

#if ENABLE_EMC_SUPPORT
void emc_init(void);
bool get_EMC_Enable(void);
int  get_EMC_NumBanks(void);
int  get_EMC_StartBank(void);
int  get_EMC_StartAddress(void);
int  get_EMC_EndAddress(void);
bool get_EMC_master(void);
#endif

uint32_t getFlags(void);
int get_wifi_key();
//
//  Functions that Visual Studio Code can't find, but are in the Arduino library.
//  So this is to just shut up some warning messages
//

extern size_t strlcpy(char *, const char *, size_t);    //  size parameter includes space for the null
extern size_t strlcat(char *, const char *, size_t);    //  size parameter includes space for the null

