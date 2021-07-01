#include "videoplayer.h"
#include "videoplayer.h"
#include "videoplayer.h"
#include "videoplayer.h"
#include <cstdlib>
#include <iostream>

void VideoPlayer::numberOfVideos()
{
	std::cout << mVideoLibrary.getVideos().size() << " videos in the library" << std::endl;
}

void VideoPlayer::showAllVideos()
{
	for (auto x : mVideoLibrary.getVideos())
	{
		std::cout << x.getTitle() << " (" << x.getVideoId() << ") ";
		std::cout << "[";

		for (auto TagIndex : x.getTags())
		{
			std::cout << TagIndex << " ";
		}

		std::cout << "]" << std::endl;
	}
}

bool VideoPlayer::DoesVideoExist(std::string videoId)
{
	for (int i = 0; i < mVideoLibrary.getVideos().size();)
	{
		if (mVideoLibrary.getVideos().at(i).getVideoId() == videoId)
		{
			return true;
		}

		i++;
	}

	return false;
}

void VideoPlayer::playVideo(const std::string& videoId)
{
	if (DoesVideoExist(videoId))
	{
		//Get a specific video - account for paused too?	
		if (IsVideoPaused)
		{
			std::cout << "The Currently playing video is paused" << std::endl;
			std::cout << "Playing" << CurrentlyPlayingVideo << std::endl;
		}

		else
		{
			if (!CurrentlyPlayingVideo.empty())
			{
				CurrentlyPlayingVideo = mVideoLibrary.getVideo(videoId)->getTitle();
			}

			else
			{
				char condition;

				std::cout << "There is currently a video playing, would you like to stop it?" << std::endl;
				std::cout << "y - for yes, n - for no" << std::endl;

				std::cin >> &condition;

				if (condition == 'y' || condition == 'Y')
				{
					CurrentlyPlayingVideo = mVideoLibrary.getVideo(videoId)->getTitle();
					return;
				}

				if (condition == 'n' || condition == 'N')
				{
					std::cout << "Continuing to play " << CurrentlyPlayingVideo;
					return;
				}
			}
		}
	}

	else
	{
		std::cout << "Cannot play video, id is invalid. It does not exist within the library!" << std::endl;
	}
}

void VideoPlayer::stopVideo()
{
	if (IsVideoPaused)
	{
		std::cout << "The Currently playing video is paused" << std::endl;
		std::cout << "Stopping" << CurrentlyPlayingVideo << std::endl;
	}

	if (CurrentlyPlayingVideo.empty())
	{
		std::cout << "Cannot stop video: No video is currently playing" << std::endl;
	}

	else
	{
		std::cout << "There is currently" << CurrentlyPlayingVideo << " playing." << std::endl;
		std::cout << "Do you want to stop it?" << std::endl;

		std::cout << "y for yes" << std::endl;
		std::cout << "n for no" << std::endl;

		char condition;

		std::cin >> &condition;

		if (condition == 'y' || condition == 'Y')
		{
			CurrentlyPlayingVideo.clear();
			std::cout << "Stopping currently playing video";
		}
		else if (condition == 'n' || condition == 'N')
		{
			std::cout << "Continuing to play " << CurrentlyPlayingVideo;
		}
	}
}

void VideoPlayer::playRandomVideo()
{
	if (!AreAllVideosFlagged())
	{
		if (!CurrentlyPlayingVideo.empty())
		{
			std::cout << "Currently playing video is not empty. Would you like to stop the current video and continue?" << std::endl;

			char condition;

			std::cout << "y for yes" << std::endl;
			std::cout << "n for no" << std::endl;

			std::cin >> &condition;

			if (condition == 'y' || condition == 'Y')
			{
				CurrentlyPlayingVideo.clear();
				std::cout << "Stopping currently playing video";
			}
			else if (condition == 'n' || condition == 'N')
			{
				std::cout << "Continuing to play " << CurrentlyPlayingVideo;
				return;
			}

		}

		int MaxBound = mVideoLibrary.getVideos().size();
		int MinBound = 0;
		int RandomNumber = rand() % MaxBound;

		std::cout << "Playing Random Video..." << std::endl;

		CurrentlyPlayingVideo = mVideoLibrary.getVideos().at(RandomNumber).getTitle();
		std::cout << "Random video selected is " << CurrentlyPlayingVideo << std::endl;
	}

	else
	{
		std::cout << "No videos available" << std::endl;
	}
}

bool VideoPlayer::AreAllVideosFlagged()
{
	int VideoCount = mVideoLibrary.getVideos().size();
	int Count = 0;

	for (auto x : mVideoLibrary.getVideos())
	{
		if (x.IsFlagged == true)
		{
			Count + 1;

			if (Count == VideoCount)
			{
				return true;
			}
		}
	}

	return false;
}

void VideoPlayer::pauseVideo()
{
	if (IsVideoPaused)
	{
		std::cout << "Pausing video: " << CurrentlyPlayingVideo << std::endl;
	}
	else
	{
		IsVideoPaused = true;
		std::cout << "Video already paused: " << CurrentlyPlayingVideo << std::endl;
	}
}

void VideoPlayer::continueVideo()
{
	if (!CurrentlyPlayingVideo.empty())
	{
		if (IsVideoPaused)
		{
			!IsVideoPaused;
			std::cout << CurrentlyPlayingVideo << " Is now playing!" << std::endl;
		}
		else
		{
			std::cout << CurrentlyPlayingVideo << " Is currently playing." << std::endl;
		}
	}
	else
	{
		std::cout << "Cannot continue video: No video is currently playing";
	}
}

void VideoPlayer::showPlaying()
{
	if (!CurrentlyPlayingVideo.empty())
	{
		std::cout << "The currently playing video is " << CurrentlyPlayingVideo << std::endl;

		if (IsVideoPaused)
		{
			std::cout << CurrentlyPlayingVideo << "Is currently paused.";
		}
		else
		{
			std::cout << CurrentlyPlayingVideo << "Is playing! Enjoy!";
		}
	}

	else
	{
		std::cout << "No video is currently playing" << std::endl;
	}

}

void VideoPlayer::createPlaylist(const std::string& playlistName)
{
	//The first element of a playlist is the name -- questionable but can't think of a better solution rn
	std::vector<std::string> Temp;

	Temp.push_back(playlistName);
	Playlists.push_back(Temp);

	std::cout << "Successfully created new playlist" << playlistName << "Currently contains no videos, add some through 'Add_Video_To_Playlist'" << std::endl;
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName, const std::string& videoId)
{
	if (IsVideoAlreadyInCollection(playlistName, videoId) == false)
	{
		if (DoesVideoExist(videoId))
		{
			AddVideo(playlistName, videoId);
			std::cout << "Added video to " << playlistName << mVideoLibrary.getVideo(videoId)->getTitle() << std::endl;
		}
		else
		{
			std::cout << "Cannot add video to " << playlistName << ": Video does not exist";
		}
	}
	else
	{
		std::cout << " Cannot add video to " << playlistName << " : video already added";
	}
}

void VideoPlayer::AddVideo(const std::string& playlistName, const std::string& videoId)
{
	//for each playlist in playlists - This is a vector of a vector of strings.
	for (auto x : Playlists)
	{
		//This should allow us to access element at element 0 of the playlist - It's name.
		if (x.at(0) == playlistName)
		{
			x.push_back(mVideoLibrary.getVideo(videoId)->getVideoId());
		}
	}
}

bool VideoPlayer::IsVideoAlreadyInCollection(const std::string& playlistName, const std::string& videoId)
{
	//for each playlist in playlists - This is a vector of a vector of strings.
	for (auto x : Playlists)
	{
		//This should allow us to access element at element 0 of the playlist - It's name.
		if (x.at(0) == playlistName)
		{
			//This is another quadratic algorithm, because of the small size of the data set, this is fine.
			//Even in the worst case it's fine. If this was larger data set I'd use a more computationally cheap algorithm.
			for (auto i : x)
			{
				if (i == mVideoLibrary.getVideo(videoId)->getTitle())
				{
					return true;
				}

				return false;
			}
		}
	}
}

void VideoPlayer::showAllPlaylists()
{
	bool AnyPlaylists = false;

	if (Playlists.empty())
	{
		AnyPlaylists = false;
	}

	if (AnyPlaylists == true)
	{
		std::cout << "Showing all playlists:" << std::endl;

		for (auto playlist : Playlists)
		{
			for (auto video : playlist)
			{
				if (video.at(0))
				{
					std::cout << "  " << video.at(0);
				}
			}
		}
	}
	else
	{
		std::cout << "No playlists exist yet" << std::endl;
	}

}

void VideoPlayer::showPlaylist(const std::string& playlistName)
{
	for (auto playlist : Playlists)
	{
		if (playlist.at(0) == playlistName)
		{
			for (auto video : playlist)
			{
				std::cout << video << std::endl;
			}
		}
	}

	std::cout << "showPlaylist needs implementation" << std::endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName, const std::string& videoId)
{
	for (auto playlist : Playlists)
	{
		if (playlist.at(0) == playlistName)
		{
			for (auto video : playlist)
			{
				if (video == mVideoLibrary.getVideo(videoId)->getVideoId())
				{
					video.erase();
					std::cout << "Removed video from " << playlistName << ":" << mVideoLibrary.getVideo(videoId)->getTitle() << std::endl;
					return;
				}
			}
		}

	}

	std::cout << "Cannot remove video from " << playlistName << ": Playlist does not exist";
	return;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName)
{
	bool isPlaylistCleared = false;
	bool DoesPlaylistExist = false;

	if (isPlaylistCleared == false)
	{
		if (DoesPlaylistExist == false)
		{
			for (auto playlist : Playlists)
			{
				if (playlist.at(0) == playlistName)
				{
					DoesPlaylistExist = true;
				}

				if (DoesPlaylistExist == true)
				{
					CleanOutPlaylist(playlistName, isPlaylistCleared);

					if (isPlaylistCleared == true)
					{
						std::cout << "Successfully removed all videos from " << playlistName << std::endl;
						return;
					}
				}
			}
		}
	}
}

void VideoPlayer::CleanOutPlaylist(const std::string& playlistName, bool IsPlaylistCleared)
{
	for (auto playlist : Playlists)
	{
		if (playlist.at(0) == playlistName)
		{
			for (auto video : playlist)
			{
				if (video != playlistName)
				{
					video.clear();
				}
			}
		}

	}

	IsPlaylistCleared = true;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName)
{
	for (auto playlist : Playlists)
	{
		for (auto video : playlist)
		{
			//I made a bad choice design using the name of the playlist as the first element. It won't play from it but...
			if (video == playlistName)
			{
				//clearing all the elements in the vector - I was thinking of using new and delete to do dynamic
				//memory allocation so that the memory where it is stored would be freed, but it's a bit scary with an object of this size.
				playlist.clear();
				std::cout << "Deleted playlist: " << playlistName << std::endl;
			}
		}
	}

	std::cout << "Cannot delete playlist " << playlistName << "Playlist does not exist";
}

void VideoPlayer::searchVideos(const std::string& searchTerm)
{
	//Simple linear search, this is a small data set. If it was larger a different sorting alogrithim would be used.
	//In the case of something where time & space complexity is important I would use a merge sort. O(n) + O(1)
	for (auto x : mVideoLibrary.getVideos())
	{
		if (x.getTitle() == searchTerm)
		{
			std::cout << x.getTitle() << std::endl;
		}
	}
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag)
{
	std::vector<std::string> VideoTag;
	VideoTag.push_back(videoTag);

	//Quadratic O(n2?)
	for (int i = 0; i > mVideoLibrary.getVideos().size(); i++)
	{
		if (mVideoLibrary.getVideos().at(i).getTags() == VideoTag)
		{
			std::cout << mVideoLibrary.getVideos().at(i).getTitle() << std::endl;
		}
	}
}

void VideoPlayer::flagVideo(const std::string& videoId)
{
	//Pretty bad, but I'm not sure how to do this as well.
	if (mVideoLibrary.getVideo(videoId)->IsFlagged == true)
	{
		std::cout << mVideoLibrary.getVideo(videoId)->getTitle() << "Is Currently flagged by the user";
	}

	else
	{
		std::cout << mVideoLibrary.getVideo(videoId)->getTitle() << "Is not currently flagged by the user, would you like to flag it?";

		char condition;

		std::cout << "y for yes" << std::endl;
		std::cout << "n for no" << std::endl;

		std::cin >> &condition;

		if (condition == 'y' || condition == 'Y')
		{
			mVideoLibrary.getVideo(videoId)->IsFlagged = true;

			if (!CurrentlyPlayingVideo.empty())
			{
				stopVideo();
			}

			std::cout << "Video was flagged";
		}
		else if (condition == 'n' || condition == 'N')
		{
			std::cout << "Video was not flagged";
		}
	}
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason)
{
	if (mVideoLibrary.getVideo(videoId)->IsFlagged == true)
	{
		std::cout << mVideoLibrary.getVideo(videoId)->getTitle() << "Is Currently flagged by the user";
		std::cout << "It is currently flagged " << mVideoLibrary.getVideo(videoId)->TagReason;
	}
	else
	{
		std::cout << mVideoLibrary.getVideo(videoId)->getTitle() << "Is not currently flagged by the user, would you like to flag it?";

		char condition;

		std::cout << "y for yes" << std::endl;
		std::cout << "n for no" << std::endl;

		std::cin >> &condition;

		if (condition == 'y' || condition == 'Y')
		{
			mVideoLibrary.getVideo(videoId)->TagReason + reason;
			mVideoLibrary.getVideo(videoId)->IsFlagged = true;

			std::cout << "Video was flagged" << " with the tag: " << reason;
		}
		else if (condition == 'n' || condition == 'N')
		{
			std::cout << "Video was not flagged";
		}
	}
}

void VideoPlayer::allowVideo(const std::string& videoId)
{
	std::string NullTag = " ";

	if (mVideoLibrary.getVideo(videoId)->IsFlagged == true)
	{
		std::cout << mVideoLibrary.getVideo(videoId)->getTitle() << "Is Currently flagged by the user";
		std::cout << "It is currently flagged " << mVideoLibrary.getVideo(videoId)->TagReason;
		std::cout << "Would you like to unflag it?" << std::endl;

		char condition;

		std::cout << "y for yes" << std::endl;
		std::cout << "n for no" << std::endl;

		std::cin >> &condition;

		if (condition == 'y' || condition == 'Y')
		{
			mVideoLibrary.getVideo(videoId)->IsFlagged = false;
			std::cout << "Video was unflagged" << std::endl;
		}
		else if (condition == 'n' || condition == 'N')
		{
			std::cout << "Video was not unflagged";
		}
	}
}

