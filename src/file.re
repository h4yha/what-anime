let get_file = file_path => {
  let ch = open_in(file_path);
  try({
    let file_content = really_input_string(ch, in_channel_length(ch));

    close_in(ch);
    file_content;
  }) {
  | e =>
    close_in_noerr(ch);
    raise(e);
  };
};