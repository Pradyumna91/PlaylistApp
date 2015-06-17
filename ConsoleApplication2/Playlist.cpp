#include "stdafx.h"
#include "Playlist.h"
#include "iostream"

Playlist::Playlist()
{
	head = nullptr;
	totalNumberOfTracks = 0;
	currentlyPlayingTrackIndex = -1;				//-1 means no track is currently playing
}

void Playlist::create(int numberOfTracks)
{
	//deleting any existing playlist
	if (head != nullptr)
	{
		Node* curNode = head;
		while (curNode != nullptr)
		{
			Node* node = curNode;
			curNode = curNode->next;
			delete node;
		}
	}

	head = new Node();
	Node* curNode = head;
	
	for (int i = 1; i < numberOfTracks; i++, curNode = curNode->next)
	{
		curNode->item = i;
		curNode->next = new Node();
	}
	curNode->item = numberOfTracks;
	curNode->next = nullptr;				//Adding the last track

	totalNumberOfTracks = numberOfTracks;
	currentlyPlayingTrackIndex = -1;

	displayPlaylist();
}

void Playlist::deleteTrackAtPosition(int position)
{
	Node* curNode = head;
	Node* trackToBeDeleted;

	if (position > totalNumberOfTracks)
	{
		throw gcnew System::ArgumentException("The track to be deleted does not exist");
	}
	else if (position == 1)
	{
		trackToBeDeleted = head;
		head = head->next;
	}
	else
	{
		for (int i = position; i > 2; --i)
		{
			curNode = curNode->next;
		}

		trackToBeDeleted = curNode->next;
		curNode->next = curNode->next->next;
	}

	if (position < currentlyPlayingTrackIndex)
	{
		--currentlyPlayingTrackIndex;
	}
	if (position == currentlyPlayingTrackIndex)
	{
		currentlyPlayingTrackIndex = -1;
	}

	--totalNumberOfTracks;
	delete trackToBeDeleted;

	displayPlaylist();
}

void Playlist::insertTrackAtPosition(int position, int trackId)
{
	Node* nodeToBeInserted = new Node();
	nodeToBeInserted->item = trackId;

	if (position > (totalNumberOfTracks + 1))				//Adding one to allow the user to add a track at the end of the playlist
	{
		throw gcnew System::ArgumentException("Invalid position for track insertion");
	}
	else if (position == 1)
	{
		nodeToBeInserted->next = head;
		head = nodeToBeInserted;
	}
	else
	{
		Node* curNode = head;
		for (int i = position; i > 2; --i)
		{
			curNode = curNode->next;
		}

		nodeToBeInserted->next = curNode->next;
		curNode->next = nodeToBeInserted;
	}

	if (position <= currentlyPlayingTrackIndex)
	{
		++currentlyPlayingTrackIndex;
	}

	++totalNumberOfTracks;

	displayPlaylist();
}

void Playlist::shuffle()
{
	//TODO implement
}

void Playlist::playTrack(int position)
{
	if (position > totalNumberOfTracks)
	{
		throw gcnew System::ArgumentException("The track you want to play does not exist");
	}
	else
	{
		currentlyPlayingTrackIndex = position;
	}

	displayPlaylist();
}

void Playlist::displayPlaylist()
{
	if (head != nullptr)
	{
		Node* curNode = head;
		int counter = 1;
		while (curNode != nullptr)
		{
			std::cout << curNode->item;
			if (counter == currentlyPlayingTrackIndex)
			{
				std::cout << "*";
			}

			if (curNode->next == nullptr)
			{
				std::cout << "\n";
			}
			else
			{
				std::cout << ",";
			}
			
			counter++;
			curNode = curNode->next;
		}
	}
}