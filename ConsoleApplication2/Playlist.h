#pragma once

struct Node
{
	int item;
	Node* next;
};

ref class Playlist
{
private:
	Node* head;
	int currentlyPlayingTrackIndex;
	int totalNumberOfTracks;

	void displayPlaylist();
	Node* shuffle(int*, int size);
	void clearPlaylist(Node* head);

public:
	Playlist();
	void create(int numberOfTracks);
	void deleteTrackAtPosition(int position);
	void insertTrackAtPosition(int position, int trackId, bool isAddingNewTrackToPlaylist);
	void shuffle();
	void playTrack(int position);
	
};

