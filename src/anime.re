open Pastel;
open Util;

[@deriving yojson({strict: false})]
type titles = {
  native: option(string),
  romaji: option(string),
  english: option(string),
};
[@deriving yojson({strict: false})]
type anilist = {
  title: titles,
  [@key "isAdult"]
  is_adult: bool,
};

// oh my gosh 🙄
[@deriving yojson]
type episode =
  | Str(string)
  | Int(int);

let episode_of_yojson =
  fun
  | `String(episode) => Ok(Str(episode))
  | `Int(episode) => Ok(Int(episode))
  | _ => Error("invalid value");

[@deriving yojson({strict: false})]
type properties = {
  anilist,
  similarity: float,
  episode: option(episode),
};

[@deriving yojson({strict: false})]
type anime = {result: array(properties)};

let get_episode =
  fun
  | Some(Str(episode_number)) => episode_number
  | Some(Int(episode_number)) => episode_number |> string_of_int
  | None => "Episode not found";

let anime_response = (anime: anime) => {
  let first_anime_result = anime.result[0];
  let print_anime_found =
    <Pastel>
      <Pastel color=Green bold=true> "✔️  Found!" </Pastel>
    </Pastel>;

  let print_anime_response =
    <Pastel>
      {print_anime(
         ~key="🗻 Title Romaji: ",
         ~value={
           first_anime_result.anilist.title.romaji |> get_title;
         },
         ~colorName=BlueBright,
       )}
      {print_anime(
         ~key="🌸 Title Native: ",
         ~value={
           first_anime_result.anilist.title.native |> get_title;
         },
         ~colorName=YellowBright,
       )}
      {print_anime(
         ~key="🗽 Title English: ",
         ~value={
           first_anime_result.anilist.title.english |> get_title;
         },
         ~colorName=CyanBright,
       )}
      {print_anime(
         ~key="📊 Similarity: ",
         ~value={
           first_anime_result.similarity |> string_of_float;
         },
         ~colorName={
           first_anime_result.similarity |> anime_similarity_color;
         },
       )}
      {print_anime(
         ~key="📺 Episode Number: ",
         ~value={
           first_anime_result.episode |> get_episode;
         },
         ~colorName=CyanBright,
       )}
      {print_anime(
         ~key="🍓 Is Adult: ",
         ~value={
           first_anime_result.anilist.is_adult |> string_of_bool;
         },
         ~colorName={
           first_anime_result.anilist.is_adult |> anime_is_adult_color;
         },
       )}
    </Pastel>;

  print_endline(print_anime_found);
  print_endline(print_anime_response);
};