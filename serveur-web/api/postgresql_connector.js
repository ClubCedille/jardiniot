var pg = require('pg');

var client = new pg.Client({
      user: 'postgres',
      password: 'myCedille@Password321',
      database: 'jardiniot',
      host: 'wp1.cedille.club',
      port: 22345
    });

client.connect(function (err) {
  if (err) throw err;

  // execute a query on our database
  client.query({text: 'INSERT INTO buckets (name) VALUES ($1)', values: ['API-Testing']}, function (err, result) {
    if (err) throw err;

    // just print the result to the console
    console.log(result.rows[0]); // outputs: { name: 'brianc' }

    // disconnect the client
    client.end(function (err) {
      if (err) throw err;
    });
  });
});
