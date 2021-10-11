open Pastel;
let anime_similarity_color = similarity =>
  switch (similarity) {
  | similarity when similarity > 0.89 => Green
  | similarity when similarity > 0.80 => Yellow
  | _ => Red
  };

let anime_is_adult_color = is_adult => is_adult ? Green : Red;

let get_title =
  fun
  | Some(title) => title
  | None => "translate not found";

let print_anime = (~key: string, ~value: string, ~colorName: Pastel.colorName) =>
  <Pastel bold=true>
    {"\n" ++ key}
    <Pastel italic=true color=colorName bold=false> value </Pastel>
  </Pastel>;

/* from http://www.codecodex.com/wiki/Generate_a_random_password_or_random_string#OCaml */
let gen_boundary = length => {
  let gen = () =>
    switch (Random.int(26 + 26 + 10)) {
    | n when n < 26 => int_of_char('a') + n
    | n when n < 26 + 26 => int_of_char('A') + n - 26
    | n => int_of_char('0') + n - 26 - 26
    };
  let gen = _ => String.make(1, char_of_int(gen()));
  String.concat("", Array.to_list(Array.init(length, gen)));
};
