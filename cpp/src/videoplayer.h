#pragma once

#include <string>
#include <array>
#include "videolibrary.h"

/**
 * A class used to represent a Video Player.
 */
class VideoPlayer {
private:

public:
	VideoLibrary mVideoLibrary;
	VideoPlayer() = default;

	// This class is not copyable to avoid expensive copies.
	VideoPlayer(const VideoPlayer&) = delete;
	VideoPlayer& operator=(const VideoPlayer&) = delete;

	// This class is movable.
	VideoPlayer(VideoPlayer&&) = default;
	VideoPlayer& operator=(VideoPlayer&&) = default;

public:

	//The video that is currently playing
	std::string CurrentlyPlayingVideo = "";
	bool IsVideoPaused;
	
	std::vector<std::vector<std::string>> Playlists;

	
	void numberOfVideos();
	void showAllVideos();
	void playVideo(const std::string& videoId);
	void stopVideo();
	void playRandomVideo();
	void pauseVideo();
	void continueVideo();
	void showPlaying();
	void createPlaylist(const std::string& playlistName);
	void addVideoToPlaylist(const std::string& playlistName, const std::string& videoId);
	void showAllPlaylists();
	void showPlaylist(const std::string& playlistName);
	void removeFromPlaylist(const std::string& playlistName, const std::string& videoId);
	void clearPlaylist(const std::string& playlistName);
	void deletePlaylist(const std::string& playlistName);
	void searchVideos(const std::string& searchTerm);
	void searchVideosWithTag(const std::string& videoTag);
	void flagVideo(const std::string& videoId);
	void flagVideo(const std::string& videoId, const std::string& reason);
	void allowVideo(const std::string& videoId);


//These are methods I implemented as part of my solution
public:

	bool DoesVideoExist(std::string videoId);
	bool AreAllVideosFlagged();

	void AddVideo(const std::string& playlistName, const std::string& videoId);
	bool IsVideoAlreadyInCollection(const std::string& playlistName, const std::string& videoId);
	void CleanOutPlaylist(const std::string& playlistName, bool IsPlaylistCleared);
};
