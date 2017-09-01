extern const char** g_KnownPlugins;

int GetKnownPluginsCount()
{
    return sizeof(g_KnownPlugins) / sizeof(g_KnownPlugins[0]);
}

const char* const GetKnownPluginHash(const int Idx_)
{
    if (Idx_ < 0 || GetKnownPluginsCount())
        return "";
        
    return g_KnownPlugins[Idx_];
}