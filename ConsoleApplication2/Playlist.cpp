#include "stdafx.h"
#include "Playlist.h"
#include "iostream"

Playlist::Playlist()
{
	head = nullptr;
	totalNumberOfTracks = 0;
	currentlyPlayingTrackIndex = -1;				//-1 means no track is currently playing
}

void Playlist::clearPlaylist(Node* root)
{
	if (root != nullptr)
	{
		Node* curNode = root;
		while (curNode != nullptr)
		{
			Node* node = curNode;
			curNode = curNode->next;
			delete node;
		}
	}
}

void Playlist::create(int numberOfTracks)
{
	//deleting any existing playlist
	clearPlaylist(head);

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

void Playlist::insertTrackAtPosition(int position, int trackId, bool isAddingNewTrackToPlaylist)
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

	//Incrementing the counts only when a new track is being added and not when track is added during shuffling
	if (isAddingNewTrackToPlaylist)
	{
		if (position <= currentlyPlayingTrackIndex)
		{
			++currentlyPlayingTrackIndex;
		}
		++totalNumberOfTracks;

		displayPlaylist();
	}
}

void Playlist::shuffle()
{
	if (totalNumberOfTracks <= 1)
	{
		if (totalNumberOfTracks < 1)
		{
			throw gcnew System::InvalidOperationException("cannot shuffle an empty playlist");
		}

		//if the playlist contains only one track it cannot be shuffled and hence displaying it directly at the end
	}
	else if (currentlyPlayingTrackIndex == -1)
	{
		Node* preShufflingPlaylist = head;
		int *ar = new int[totalNumberOfTracks];
		Node* curNode = head;
		for (int i = 0; i < totalNumberOfTracks; i++, curNode = curNode->next)
		{
			ar[i] = curNode->item;
		}
		head = shuffle(ar, totalNumberOfTracks);
		clearPlaylist(preShufflingPlaylist);
	}
	else
	{
		int currentlyPlayingItem;
		int *ar = new int[totalNumberOfTracks - 1];
		Node* curNode = head;

		for (int i = 1, j = 0; i <= totalNumberOfTracks; i++, curNode = curNode->next)
		{
			if (i == currentlyPlayingTrackIndex)
			{
				currentlyPlayingItem = curNode->item;
				continue;
			}
			ar[j] = curNode->item;
			j = j + 1;
		}

		Node* shuffledList = shuffle(ar, totalNumberOfTracks - 1);
		clearPlaylist(head);
		head = shuffledList;
		//Inserting the currently playing item into its position
		insertTrackAtPosition(currentlyPlayingTrackIndex, currentlyPlayingItem, false);
	}

	displayPlaylist();
}

Node* Playlist::shuffle(int* ar, int size)
{
	System::Random^ rand = gcnew System::Random();
	
	//Fisher-Yates shuffle
	for (int i = size - 1; i >= 1; i--)
	{
		int swapIdx = rand->Next(i);
		int temp = ar[swapIdx];
		ar[swapIdx] = ar[i];
		ar[i] = temp;
	}

	Node* shuffledList = new Node();
	Node* curNode = shuffledList;
	for (int i = 0; i < size - 1; i++, curNode = curNode->next)
	{
		curNode->item = ar[i];
		curNode->next = new Node();
	}
	curNode->item = ar[size - 1];					//Adding the last element
	curNode->next = nullptr;

	return shuffledList;
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