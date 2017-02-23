/**
* @brief Structure containing main config parameters

**/
struct MainConfig {

    /// Constructor giving values to all parameters
    MainConfig();

    /// csv version2 medium working point 
    const double csvV2WPmedium;


};

// The global that you will use to fetch the configurations during runtime.
extern const MainConfig mainConfig;
