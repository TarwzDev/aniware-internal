#pragma once

enum Hitboxes_t : int
{
	hitbox_head = 0,
	hitbox_neck,
	hitbox_pelvis,
	hitbox_stomach,
	hitbox_lower_chest,
	hitbox_chest,
	hitbox_upper_chest,
	hitbox_right_thigh,
	hitbox_left_thigh,
	hitbox_right_calf,
	hitbox_left_calf,
	hitbox_right_foot,
	hitbox_left_foot,
	hitbox_right_hand,
	hitbox_left_hand,
	hitbox_right_upper_arm,
	hitbox_right_forearm,
	hitbox_left_upper_arm,
	hitbox_left_forearm,
	hitbox_max
};

enum Hitgroups_t : int
{
	hitgroup_generic,
	hitgroup_head,
	hitgroup_chest,
	hitgroup_stomach,
	hitgroup_leftarm,
	hitgroup_rightarm,
	hitgroup_leftleg,
	hitgroup_rightleg = 7,
	hitgroup_gear = 10
};

struct studio_bone_t
{
	int name_index;
	int parent;
	int bone_controller[ 6 ];

	math::vec3_t pos;
	math::vec4_t quaternion;
	math::vec3_t rotation;

	math::vec3_t pos_scale;
	math::vec3_t rot_scale;

	math::matrix3x4_t pose_to_bone;
	math::vec4_t quat_alignement;
	int flags;
	int proc_type;
	int proc_index;
	int physics_bone;

	int contents;
	int surf_prop_lookup;
	int unused[ 7 ];
};

struct studio_box_t
{
	int bone;
	int group;
	math::vec3_t mins;
	math::vec3_t maxs;
	int name_index;
	int pad01[ 3 ];
	float radius;
	int pad02[ 4 ];
};

struct studio_hitbox_set_t
{
	int name_index;
	int hitbox_count;
	int hitbox_index;

	studio_box_t* hitbox( int index )
	{
		return reinterpret_cast< studio_box_t* >( reinterpret_cast< unsigned char* >( this ) + hitbox_index )  + index;
	}
};

struct studio_hdr_t 
{
	int id;
	int version;
	long checksum;
	char name_char_array[ 64 ];
	int length;

	math::vec3_t eye_pos;
	math::vec3_t illium_pos;
	math::vec3_t hull_mins;
	math::vec3_t hull_maxs;
	math::vec3_t mins;
	math::vec3_t maxs;

	int flags;
	int bones_count;
	int bone_index;
	int bone_controllers_count;
	int bone_controller_index;
	int hitbox_sets_count;
	int hitbox_set_index;
	int local_anim_count;
	int local_anim_index;
	int local_seq_count;
	int local_seq_index;
	int activity_list_version;
	int events_indexed;
	int textures_count;
	int texture_index;

	studio_hitbox_set_t* hitbox_set( int index )
	{
		if ( index > hitbox_sets_count )
			return nullptr;

		return reinterpret_cast< studio_hitbox_set_t* >(reinterpret_cast<unsigned char*>(this) + hitbox_set_index ) + index;
	}

	studio_bone_t* bone( int index)
	{
		if ( index > bones_count )
			return nullptr;

		return reinterpret_cast< studio_bone_t* >( reinterpret_cast< unsigned char *>( this ) + bone_index )  + index;
	}
};