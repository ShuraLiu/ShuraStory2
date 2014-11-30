//
//  ResourceLoader.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/30.
//
//

#ifndef __ShuraStory__ResourceLoader__
#define __ShuraStory__ResourceLoader__

#include "cocos2d.h"

class ResourceLoader
{
    struct BaseInfo
    {
        std::string fileName;
        std::string groupID;
    };
    
    struct TextureInfo : public BaseInfo
    {
        cocos2d::Texture2D::PixelFormat format;
    };
    
    struct SpriteFrameInfo : public BaseInfo
    {
        
    };
    
    struct BitmapFontInfo : public BaseInfo
    {
        
    };
    
    typedef std::vector<TextureInfo> TextureInfoArray;
    typedef std::vector<SpriteFrameInfo> SpriteFrameInfoArray;
    typedef std::vector<BitmapFontInfo> BitmapFontInfoArray;
    
public:
    typedef std::function<void(int , int)> ResourceLoadProgressCallback;
    typedef std::function<void()> ResourceLoadStateCallback;
    
public:
    explicit ResourceLoader(const std::vector<std::string>& groups, const ResourceLoadProgressCallback& callback, const ResourceLoadStateCallback& startCallback, const ResourceLoadStateCallback endCallback);
    
public:
    void startLoad();
    
private:
    cocos2d::Texture2D::PixelFormat translateTextureFormat(const std::string& format);
    void onAsyncTextureLoadCallback(cocos2d::Texture2D* tex);
    void loadResourceInCocosThread();
    void loadResourcePerFrame(float dt);
    void notifyProgress();
    void notifyStart();
    void notifyEnd();
    
private:
    TextureInfoArray _arrayTextures;
    SpriteFrameInfoArray _arraySpriteFrames;
    BitmapFontInfoArray _arrayBitmapFonts;
    
private:
    int _textureLoadProgress;
    int _spriteLoadProgress;
    int _bitmapFontLoadProgress;
    int _curResourceCount;
    int _totalResourceCount;
    ResourceLoadProgressCallback _callback;
    ResourceLoadStateCallback _startCallback;
    ResourceLoadStateCallback _endCallback;
};

#endif /* defined(__ShuraStory__ResourceLoader__) */
